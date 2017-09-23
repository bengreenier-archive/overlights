using Q42.HueApi;
using Q42.HueApi.ColorConverters;
using Q42.HueApi.ColorConverters.Original;
using RzChroma;
using RzChroma.Data;
using RzChroma.Data.Keyboard;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO.Pipes;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Overlights
{
    public partial class MainPage : Form
    {
        private Thread commThread;
        private Thread hueThread;
        private HueClient hueClient;
        private PictureBox contextMenuPictureBox;

        public MainPage()
        {
            InitializeComponent();
            ResizeTableToRuntimeRequirements();

            // configure the enabled menu appropriately
            pluginMenuEnabled.Checked = RzChromaPlugin.Enabled;

            hueThread = new Thread(HuelightThreadAsync);
            hueThread.Start();

            commThread = new Thread(CommunicationThread);
            commThread.Start();
        }

        private async void HuelightThreadAsync(object state)
        {
            var registryKey = Application.UserAppDataRegistry.OpenSubKey("Overlights");

            if (registryKey == null)
            {
                return;
            }

            var bridgeIp = registryKey.GetValue("BridgeIp", "") as string;
            var bridgePass = registryKey.GetValue("BridgePassword", "") as string;

            if (string.IsNullOrEmpty(bridgeIp) || string.IsNullOrEmpty(bridgePass))
            {
                return;
            }

            var client = new LocalHueClient(bridgeIp);

            client.Initialize(bridgePass);

            var lights = await client.GetLightsAsync();

            BuildLightMenus(lights);

            hueClient = client;
        }

        private async void CommunicationThread(object state)
        {
            var client = await RzChromaPlugin.CreateStreamAsync();
            
            using (var sr = new RzChromaStreamReader(client))
            {
                while (client.CanRead)
                {
                    var msg = sr.ReadMessage();

                    if (msg.Type == DataType.Keyboard)
                    {
                        var data = msg.As<IKeyboardData>();

                        if (data.EventType == KeyboardDataType.CHROMA_CUSTOM ||
                            data.EventType == KeyboardDataType.CHROMA_CUSTOM_KEY)
                        {
                            var evt = data.As<CustomKeyboardData>();

                            for (var i = 0; i < evt.ColorMap.Length; i++)
                            {
                                for (var j = 0; j < evt.ColorMap[i].Length; j++)
                                {
                                    var color = evt.ColorMap[i][j];
                                    var control = this.keyLayout.GetControlFromPosition(j, i);
                                    control.BackColor = System.Drawing.Color.FromArgb(255, color.R, color.G, color.B);
                                }
                            }
                        }
                    }
                }
            }
        }

        private void ResizeTableToRuntimeRequirements()
        {
            this.keyLayout.RowCount = CustomKeyboardData.MaxRows;
            this.keyLayout.ColumnCount = CustomKeyboardData.MaxCols;

            for (var i = 0; i < CustomKeyboardData.MaxRows; i++)
            {
                for (var j = 0; j < CustomKeyboardData.MaxCols; j++)
                {
                    var defaultPictBox = new PictureBox
                    {
                        BackColor = this.BackColor
                    };

                    defaultPictBox.MouseClick += pictBox_Click;
                    defaultPictBox.BackColorChanged += pictBox_BackColorChanged;
                    defaultPictBox.Paint += pictBox_Paint;

                    this.keyLayout.Controls.Add(defaultPictBox, j, i);
                }
            }
        }
        
        private void BuildLightMenus(IEnumerable<Light> lights)
        {
            foreach (var light in lights)
            {
                var item = contextMenu.Items.Add(light.Name + " - " + light.Id);
                item.Tag = light.Id;
            }
        }
        
        protected override void OnClosing(CancelEventArgs e)
        {
            if (commThread != null && commThread.IsAlive)
            {
                commThread.Abort();
                commThread.Join();
            }

            if (hueThread != null && hueThread.IsAlive)
            {
                hueThread.Abort();
                hueThread.Join();
            }

            base.OnClosing(e);
        }

        private void pictBox_Click(object sender, MouseEventArgs e)
        {
            if (contextMenu.Items.Count > 0)
            {
                contextMenuPictureBox = sender as PictureBox;
                contextMenu.ItemClicked += ContextMenu_ItemClicked;
                contextMenu.Show(sender as PictureBox, e.Location);
            }
        }

        private async void pictBox_BackColorChanged(object sender, EventArgs e)
        {
            var box = (sender as PictureBox);

            if (box.Tag != null && hueClient != null)
            {
                var lightId = box.Tag as string;
                
                var command = new LightCommand().SetColor(new RGBColor(box.BackColor.R, box.BackColor.G, box.BackColor.B));

                try
                {
                    await hueClient.SendCommandAsync(command, new List<string>() { lightId });
                }
                catch (Exception)
                {
                    // swallow
                }
            }
        }

        private void pictBox_Paint(object sender, PaintEventArgs e)
        {
            var PB = sender as PictureBox;
            e.Graphics.TextRenderingHint = System.Drawing.Text.TextRenderingHint.ClearTypeGridFit;

            string text = PB.Tag as string;

            SizeF textSize = e.Graphics.MeasureString(text, PB.Font);
            PointF locationToDraw = new PointF();
            locationToDraw.X = (PB.Width / 2) - (textSize.Width / 2);
            locationToDraw.Y = (PB.Height / 2) - (textSize.Height / 2);

            e.Graphics.DrawString(text, PB.Font, Brushes.Black, locationToDraw);
        }

        private async void ContextMenu_ItemClicked(object sender, ToolStripItemClickedEventArgs e)
        {
            // parse out into the light id
            var lightId = e.ClickedItem.Tag as string;

            // set it on the contextMenuPicture
            contextMenuPictureBox.Tag = lightId;
            contextMenuPictureBox.Refresh();

            // if it isn't on, turn it on
            // we could do this in pictBox_BackColorChanged
            // but that's the hot path, so instead we do here and hope the user doesn't
            // manually go in and change it
            if (hueClient != null)
            {
                var light = await hueClient.GetLightAsync(lightId);
                
                if (!light.State.On)
                {
                    var command = new LightCommand().TurnOn();

                    try
                    {
                        await hueClient.SendCommandAsync(command, new List<string>() { light.Id });
                    }
                    catch (Exception)
                    {
                        // swallow
                    }
                }
            }
        }

        private void HueMenuSetup_Click(object sender, EventArgs e)
        {
            var huePage = new HueSetupPage();
            huePage.Show();
        }

        private void HueMenuClearAll_Click(object sender, EventArgs e)
        {
            for (var i = 0; i < this.keyLayout.RowCount; i++)
            {
                for (var j = 0; j < this.keyLayout.ColumnCount; j++)
                {
                    // remove the tags
                    this.keyLayout.GetControlFromPosition(j, i).Tag = null;
                }
            }
        }

        private void PluginMenuEnabled_Click(object sender, EventArgs e)
        {
            var menu = sender as ToolStripMenuItem;

            RzChromaPlugin.Enabled = !menu.Checked;

            menu.Checked = !menu.Checked;
        }
    }
}
