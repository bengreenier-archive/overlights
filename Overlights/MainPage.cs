﻿using RzChroma.Managed;
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

        public MainPage()
        {
            InitializeComponent();
            ResizeTableToRuntimeRequirements();

            commThread = new Thread(CommunicationThread);
            commThread.Start();
        }

        private void CommunicationThread(object state)
        {
            var client = new NamedPipeClientStream(".", "RzChromaData", PipeDirection.In);

            client.Connect();

            using (var sr = new RzChromaStreamReader(client))
            {
                while (client.IsConnected)
                {
                    var msg = sr.ReadMessage();

                    if (msg.Type == NativeLayouts.RZKEYBOARDTYPE.CHROMA_CUSTOM ||
                        msg.Type == NativeLayouts.RZKEYBOARDTYPE.CHROMA_CUSTOM_KEY)
                    {
                        var data = msg as RzChromaKeyboardCustomData;

                        for (var i = 0; i < data.ColorMap.Length; i++)
                        {
                            for (var j = 0; j < data.ColorMap[i].Length; j++)
                            {
                                var color = data.ColorMap[i][j];
                                var control = this.keyLayout.GetControlFromPosition(j, i);
                                control.BackColor = Color.FromArgb(255, color.R, color.G, color.B);
                            }
                        }
                    }
                }
            }
        }

        private void ResizeTableToRuntimeRequirements()
        {
            this.keyLayout.RowCount = NativeLayouts.RZKEYBOARD_MAX_ROWS;
            this.keyLayout.ColumnCount = NativeLayouts.RZKEYBOARD_MAX_COLUMNS;

            for (var i = 0; i < NativeLayouts.RZKEYBOARD_MAX_ROWS; i++)
            {
                for (var j = 0; j < NativeLayouts.RZKEYBOARD_MAX_COLUMNS; j++)
                {
                    var defaultPictBox = new PictureBox
                    {
                        BackColor = this.BackColor
                    };

                    this.keyLayout.Controls.Add(defaultPictBox, j, i);
                }
            }
        }
        
        protected override void OnClosing(CancelEventArgs e)
        {
            if (commThread != null)
            {
                commThread.Abort();
                commThread.Join();
            }

            base.OnClosing(e);
        }
    }
}
