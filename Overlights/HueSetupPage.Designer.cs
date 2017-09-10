namespace Overlights
{
    partial class HueSetupPage
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.ScanButton = new System.Windows.Forms.Button();
            this.CurrentDeviceTextBox = new System.Windows.Forms.TextBox();
            this.CurrentDeviceLabel = new System.Windows.Forms.Label();
            this.CurrentPasswordLabel = new System.Windows.Forms.Label();
            this.CurrentPasswordTextBox = new System.Windows.Forms.TextBox();
            this.StatusText = new System.Windows.Forms.TextBox();
            this.SuspendLayout();
            // 
            // ScanButton
            // 
            this.ScanButton.Location = new System.Drawing.Point(12, 163);
            this.ScanButton.Name = "ScanButton";
            this.ScanButton.Size = new System.Drawing.Size(85, 23);
            this.ScanButton.TabIndex = 0;
            this.ScanButton.Text = "Scan Network";
            this.ScanButton.UseVisualStyleBackColor = true;
            this.ScanButton.Click += new System.EventHandler(this.ScanButton_Click);
            // 
            // CurrentDeviceTextBox
            // 
            this.CurrentDeviceTextBox.Location = new System.Drawing.Point(108, 19);
            this.CurrentDeviceTextBox.Name = "CurrentDeviceTextBox";
            this.CurrentDeviceTextBox.ReadOnly = true;
            this.CurrentDeviceTextBox.Size = new System.Drawing.Size(100, 20);
            this.CurrentDeviceTextBox.TabIndex = 1;
            this.CurrentDeviceTextBox.Text = "No Device";
            // 
            // CurrentDeviceLabel
            // 
            this.CurrentDeviceLabel.AutoSize = true;
            this.CurrentDeviceLabel.Location = new System.Drawing.Point(12, 22);
            this.CurrentDeviceLabel.Name = "CurrentDeviceLabel";
            this.CurrentDeviceLabel.Size = new System.Drawing.Size(78, 13);
            this.CurrentDeviceLabel.TabIndex = 2;
            this.CurrentDeviceLabel.Text = "Current Device";
            // 
            // CurrentPasswordLabel
            // 
            this.CurrentPasswordLabel.AutoSize = true;
            this.CurrentPasswordLabel.Location = new System.Drawing.Point(12, 52);
            this.CurrentPasswordLabel.Name = "CurrentPasswordLabel";
            this.CurrentPasswordLabel.Size = new System.Drawing.Size(90, 13);
            this.CurrentPasswordLabel.TabIndex = 4;
            this.CurrentPasswordLabel.Text = "Current Password";
            // 
            // CurrentPasswordTextBox
            // 
            this.CurrentPasswordTextBox.Location = new System.Drawing.Point(108, 49);
            this.CurrentPasswordTextBox.Name = "CurrentPasswordTextBox";
            this.CurrentPasswordTextBox.ReadOnly = true;
            this.CurrentPasswordTextBox.Size = new System.Drawing.Size(100, 20);
            this.CurrentPasswordTextBox.TabIndex = 3;
            this.CurrentPasswordTextBox.Text = "No Password";
            // 
            // StatusText
            // 
            this.StatusText.Location = new System.Drawing.Point(229, 19);
            this.StatusText.Multiline = true;
            this.StatusText.Name = "StatusText";
            this.StatusText.ReadOnly = true;
            this.StatusText.Size = new System.Drawing.Size(208, 167);
            this.StatusText.TabIndex = 5;
            // 
            // HueSetupPage
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoSize = true;
            this.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.ClientSize = new System.Drawing.Size(464, 208);
            this.Controls.Add(this.StatusText);
            this.Controls.Add(this.CurrentPasswordLabel);
            this.Controls.Add(this.CurrentPasswordTextBox);
            this.Controls.Add(this.CurrentDeviceLabel);
            this.Controls.Add(this.CurrentDeviceTextBox);
            this.Controls.Add(this.ScanButton);
            this.Name = "HueSetupPage";
            this.Text = "Hue Setup";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button ScanButton;
        private System.Windows.Forms.TextBox CurrentDeviceTextBox;
        private System.Windows.Forms.Label CurrentDeviceLabel;
        private System.Windows.Forms.Label CurrentPasswordLabel;
        private System.Windows.Forms.TextBox CurrentPasswordTextBox;
        private System.Windows.Forms.TextBox StatusText;
    }
}