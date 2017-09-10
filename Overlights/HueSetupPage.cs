using Q42.HueApi;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Overlights
{
    public partial class HueSetupPage : Form
    {
        public HueSetupPage()
        {
            InitializeComponent();
            TryLoadCurrent();
        }

        private void TryLoadCurrent()
        {
            var registryKey = Application.UserAppDataRegistry.OpenSubKey("Overlights");

            if (registryKey == null)
            {
                return;
            }

            var bridgeIp = registryKey.GetValue("BridgeIp", "No Device") as string;
            var bridgePass = registryKey.GetValue("BridgePassword", "No Password") as string;

            CurrentDeviceTextBox.Text = bridgeIp;
            CurrentPasswordTextBox.Text = bridgePass;
        }

        private async void ScanButton_Click(object sender, EventArgs e)
        {
            var locator = new HttpBridgeLocator();

            var bridges = await locator.LocateBridgesAsync(TimeSpan.FromSeconds(30));
            var bridge = bridges.FirstOrDefault();

            StatusText.Text += $"Connecting to {bridge.BridgeId}...";

            var client = new LocalHueClient(bridge.IpAddress);

            StatusText.Text += $"Press the link button in the next 10s...";

            await Task.Run(() => { System.Threading.Thread.Sleep(10 * 1000); });

            var appPassword = await client.RegisterAsync("Overlights", Environment.MachineName);

            var registryKey = Application.UserAppDataRegistry.OpenSubKey("Overlights");

            if (registryKey == null)
            {
                registryKey = Application.UserAppDataRegistry.CreateSubKey("Overlights");
            }

            registryKey.SetValue("BridgeIp", bridge.IpAddress);
            registryKey.SetValue("BridgePassword", appPassword);

            CurrentDeviceTextBox.Text = bridge.IpAddress;
            CurrentPasswordTextBox.Text = appPassword;

            StatusText.Text += "Connected";
        }
    }
}
