namespace Overlights
{
    partial class MainPage
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
            this.components = new System.ComponentModel.Container();
            this.keyLayout = new System.Windows.Forms.TableLayoutPanel();
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.setupToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.hueMenu = new System.Windows.Forms.ToolStripMenuItem();
            this.hueMenuSetup = new System.Windows.Forms.ToolStripMenuItem();
            this.hueMenuClearLights = new System.Windows.Forms.ToolStripMenuItem();
            this.pluginMenu = new System.Windows.Forms.ToolStripMenuItem();
            this.pluginMenuEnabled = new System.Windows.Forms.ToolStripMenuItem();
            this.contextMenu = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.menuStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // keyLayout
            // 
            this.keyLayout.AutoSize = true;
            this.keyLayout.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.keyLayout.CellBorderStyle = System.Windows.Forms.TableLayoutPanelCellBorderStyle.Single;
            this.keyLayout.ColumnCount = 2;
            this.keyLayout.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.keyLayout.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.keyLayout.Location = new System.Drawing.Point(0, 52);
            this.keyLayout.Margin = new System.Windows.Forms.Padding(6);
            this.keyLayout.Name = "keyLayout";
            this.keyLayout.RowCount = 2;
            this.keyLayout.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.keyLayout.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.keyLayout.Size = new System.Drawing.Size(3, 3);
            this.keyLayout.TabIndex = 0;
            // 
            // menuStrip1
            // 
            this.menuStrip1.ImageScalingSize = new System.Drawing.Size(32, 32);
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.setupToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Padding = new System.Windows.Forms.Padding(12, 4, 0, 4);
            this.menuStrip1.Size = new System.Drawing.Size(1654, 46);
            this.menuStrip1.TabIndex = 1;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // setupToolStripMenuItem
            // 
            this.setupToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.hueMenu,
            this.pluginMenu});
            this.setupToolStripMenuItem.Name = "setupToolStripMenuItem";
            this.setupToolStripMenuItem.Size = new System.Drawing.Size(89, 38);
            this.setupToolStripMenuItem.Text = "Setup";
            // 
            // hueMenu
            // 
            this.hueMenu.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.hueMenuSetup,
            this.hueMenuClearLights});
            this.hueMenu.Name = "hueMenu";
            this.hueMenu.Size = new System.Drawing.Size(268, 38);
            this.hueMenu.Text = "Hue";
            // 
            // hueMenuSetup
            // 
            this.hueMenuSetup.Name = "hueMenuSetup";
            this.hueMenuSetup.Size = new System.Drawing.Size(334, 38);
            this.hueMenuSetup.Text = "Setup";
            this.hueMenuSetup.Click += new System.EventHandler(this.HueMenuSetup_Click);
            // 
            // hueMenuClearLights
            // 
            this.hueMenuClearLights.Name = "hueMenuClearLights";
            this.hueMenuClearLights.Size = new System.Drawing.Size(334, 38);
            this.hueMenuClearLights.Text = "Clear Mapped Lights";
            this.hueMenuClearLights.Click += new System.EventHandler(this.HueMenuClearAll_Click);
            // 
            // pluginMenu
            // 
            this.pluginMenu.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.pluginMenuEnabled});
            this.pluginMenu.Name = "pluginMenu";
            this.pluginMenu.Size = new System.Drawing.Size(268, 38);
            this.pluginMenu.Text = "Plugin";
            // 
            // pluginMenuEnabled
            // 
            this.pluginMenuEnabled.Name = "pluginMenuEnabled";
            this.pluginMenuEnabled.Size = new System.Drawing.Size(268, 38);
            this.pluginMenuEnabled.Text = "Enabled";
            this.pluginMenuEnabled.Click += new System.EventHandler(this.PluginMenuEnabled_Click);
            // 
            // contextMenu
            // 
            this.contextMenu.ImageScalingSize = new System.Drawing.Size(32, 32);
            this.contextMenu.Name = "contextMenu";
            this.contextMenu.Size = new System.Drawing.Size(61, 4);
            // 
            // MainPage
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(12F, 25F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoSize = true;
            this.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.ClientSize = new System.Drawing.Size(1654, 587);
            this.Controls.Add(this.keyLayout);
            this.Controls.Add(this.menuStrip1);
            this.MainMenuStrip = this.menuStrip1;
            this.Margin = new System.Windows.Forms.Padding(6);
            this.Name = "MainPage";
            this.Text = "Overlights";
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TableLayoutPanel keyLayout;
        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem setupToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem hueMenu;
        private System.Windows.Forms.ContextMenuStrip contextMenu;
        private System.Windows.Forms.ToolStripMenuItem pluginMenu;
        private System.Windows.Forms.ToolStripMenuItem pluginMenuEnabled;
        private System.Windows.Forms.ToolStripMenuItem hueMenuSetup;
        private System.Windows.Forms.ToolStripMenuItem hueMenuClearLights;
    }
}

