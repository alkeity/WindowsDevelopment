namespace Clock
{
	partial class MainForm
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
			System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(MainForm));
			this.labelTime = new System.Windows.Forms.Label();
			this.contextMenuTray = new System.Windows.Forms.ContextMenuStrip(this.components);
			this.showControlsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.showDatToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.toolStripSeparator2 = new System.Windows.Forms.ToolStripSeparator();
			this.fontToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.digital7ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.systemFontsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.colorsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.backgroundColorToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.foregroundColorToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.iconToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.toolStripSeparator3 = new System.Windows.Forms.ToolStripSeparator();
			this.alarmToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
			this.closeToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.timer1 = new System.Windows.Forms.Timer(this.components);
			this.cbShowDate = new System.Windows.Forms.CheckBox();
			this.notifyIconResize = new System.Windows.Forms.NotifyIcon(this.components);
			this.btnShowControls = new System.Windows.Forms.Button();
			this.cbPin = new System.Windows.Forms.CheckBox();
			this.cbPinBtn = new System.Windows.Forms.CheckBox();
			this.axPlayer = new AxWMPLib.AxWindowsMediaPlayer();
			this.startOnStartupToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.contextMenuTray.SuspendLayout();
			((System.ComponentModel.ISupportInitialize)(this.axPlayer)).BeginInit();
			this.SuspendLayout();
			// 
			// labelTime
			// 
			this.labelTime.AutoSize = true;
			this.labelTime.BackColor = System.Drawing.SystemColors.Control;
			this.labelTime.ContextMenuStrip = this.contextMenuTray;
			this.labelTime.Font = new System.Drawing.Font("Microsoft Sans Serif", 32F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
			this.labelTime.Location = new System.Drawing.Point(12, 9);
			this.labelTime.Name = "labelTime";
			this.labelTime.Size = new System.Drawing.Size(219, 51);
			this.labelTime.TabIndex = 0;
			this.labelTime.Text = "labelTime";
			this.labelTime.DoubleClick += new System.EventHandler(this.labelTime_DoubleClick);
			// 
			// contextMenuTray
			// 
			this.contextMenuTray.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.showControlsToolStripMenuItem,
            this.showDatToolStripMenuItem,
            this.toolStripSeparator2,
            this.fontToolStripMenuItem,
            this.colorsToolStripMenuItem,
            this.iconToolStripMenuItem,
            this.toolStripSeparator3,
            this.alarmToolStripMenuItem,
            this.toolStripSeparator1,
            this.startOnStartupToolStripMenuItem,
            this.closeToolStripMenuItem});
			this.contextMenuTray.Name = "contextMenuTray";
			this.contextMenuTray.Size = new System.Drawing.Size(181, 220);
			// 
			// showControlsToolStripMenuItem
			// 
			this.showControlsToolStripMenuItem.Checked = true;
			this.showControlsToolStripMenuItem.CheckOnClick = true;
			this.showControlsToolStripMenuItem.CheckState = System.Windows.Forms.CheckState.Checked;
			this.showControlsToolStripMenuItem.Name = "showControlsToolStripMenuItem";
			this.showControlsToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
			this.showControlsToolStripMenuItem.Text = "Show controls";
			this.showControlsToolStripMenuItem.Click += new System.EventHandler(this.showControlsToolStripMenuItem_Click);
			// 
			// showDatToolStripMenuItem
			// 
			this.showDatToolStripMenuItem.CheckOnClick = true;
			this.showDatToolStripMenuItem.Name = "showDatToolStripMenuItem";
			this.showDatToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
			this.showDatToolStripMenuItem.Text = "Show date";
			this.showDatToolStripMenuItem.Click += new System.EventHandler(this.showDatToolStripMenuItem_Click);
			// 
			// toolStripSeparator2
			// 
			this.toolStripSeparator2.Name = "toolStripSeparator2";
			this.toolStripSeparator2.Size = new System.Drawing.Size(177, 6);
			// 
			// fontToolStripMenuItem
			// 
			this.fontToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.digital7ToolStripMenuItem,
            this.systemFontsToolStripMenuItem});
			this.fontToolStripMenuItem.Name = "fontToolStripMenuItem";
			this.fontToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
			this.fontToolStripMenuItem.Text = "Font";
			// 
			// digital7ToolStripMenuItem
			// 
			this.digital7ToolStripMenuItem.Name = "digital7ToolStripMenuItem";
			this.digital7ToolStripMenuItem.Size = new System.Drawing.Size(144, 22);
			this.digital7ToolStripMenuItem.Text = "digital-7";
			this.digital7ToolStripMenuItem.Click += new System.EventHandler(this.digital7ToolStripMenuItem_Click);
			// 
			// systemFontsToolStripMenuItem
			// 
			this.systemFontsToolStripMenuItem.Name = "systemFontsToolStripMenuItem";
			this.systemFontsToolStripMenuItem.Size = new System.Drawing.Size(144, 22);
			this.systemFontsToolStripMenuItem.Text = "System Fonts";
			this.systemFontsToolStripMenuItem.Click += new System.EventHandler(this.systemFontsToolStripMenuItem_Click);
			// 
			// colorsToolStripMenuItem
			// 
			this.colorsToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.backgroundColorToolStripMenuItem,
            this.foregroundColorToolStripMenuItem});
			this.colorsToolStripMenuItem.Name = "colorsToolStripMenuItem";
			this.colorsToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
			this.colorsToolStripMenuItem.Text = "Colors";
			// 
			// backgroundColorToolStripMenuItem
			// 
			this.backgroundColorToolStripMenuItem.Name = "backgroundColorToolStripMenuItem";
			this.backgroundColorToolStripMenuItem.Size = new System.Drawing.Size(168, 22);
			this.backgroundColorToolStripMenuItem.Text = "Background color";
			this.backgroundColorToolStripMenuItem.Click += new System.EventHandler(this.backgroundColorToolStripMenuItem_Click);
			// 
			// foregroundColorToolStripMenuItem
			// 
			this.foregroundColorToolStripMenuItem.Name = "foregroundColorToolStripMenuItem";
			this.foregroundColorToolStripMenuItem.Size = new System.Drawing.Size(168, 22);
			this.foregroundColorToolStripMenuItem.Text = "Foreground color";
			this.foregroundColorToolStripMenuItem.Click += new System.EventHandler(this.foregroundColorToolStripMenuItem_Click);
			// 
			// iconToolStripMenuItem
			// 
			this.iconToolStripMenuItem.Name = "iconToolStripMenuItem";
			this.iconToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
			this.iconToolStripMenuItem.Text = "Icon";
			this.iconToolStripMenuItem.Click += new System.EventHandler(this.iconToolStripMenuItem_Click);
			// 
			// toolStripSeparator3
			// 
			this.toolStripSeparator3.Name = "toolStripSeparator3";
			this.toolStripSeparator3.Size = new System.Drawing.Size(177, 6);
			// 
			// alarmToolStripMenuItem
			// 
			this.alarmToolStripMenuItem.Name = "alarmToolStripMenuItem";
			this.alarmToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
			this.alarmToolStripMenuItem.Text = "Alarm";
			this.alarmToolStripMenuItem.Click += new System.EventHandler(this.alarmToolStripMenuItem_Click);
			// 
			// toolStripSeparator1
			// 
			this.toolStripSeparator1.Name = "toolStripSeparator1";
			this.toolStripSeparator1.Size = new System.Drawing.Size(177, 6);
			// 
			// closeToolStripMenuItem
			// 
			this.closeToolStripMenuItem.Name = "closeToolStripMenuItem";
			this.closeToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
			this.closeToolStripMenuItem.Text = "Close";
			this.closeToolStripMenuItem.Click += new System.EventHandler(this.closeToolStripMenuItem_Click);
			// 
			// timer1
			// 
			this.timer1.Enabled = true;
			this.timer1.Interval = 1000;
			this.timer1.Tick += new System.EventHandler(this.timer1_Tick);
			// 
			// cbShowDate
			// 
			this.cbShowDate.AutoSize = true;
			this.cbShowDate.Font = new System.Drawing.Font("Microsoft Sans Serif", 13F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
			this.cbShowDate.Location = new System.Drawing.Point(21, 157);
			this.cbShowDate.Name = "cbShowDate";
			this.cbShowDate.Size = new System.Drawing.Size(117, 26);
			this.cbShowDate.TabIndex = 1;
			this.cbShowDate.Text = "Show Date";
			this.cbShowDate.UseVisualStyleBackColor = true;
			this.cbShowDate.CheckedChanged += new System.EventHandler(this.checkBox1_CheckedChanged);
			// 
			// notifyIconResize
			// 
			this.notifyIconResize.BalloonTipIcon = System.Windows.Forms.ToolTipIcon.Info;
			this.notifyIconResize.BalloonTipText = "Clock gone to tray!";
			this.notifyIconResize.ContextMenuStrip = this.contextMenuTray;
			this.notifyIconResize.Icon = ((System.Drawing.Icon)(resources.GetObject("notifyIconResize.Icon")));
			this.notifyIconResize.Text = "MainForm";
			this.notifyIconResize.Visible = true;
			this.notifyIconResize.MouseDoubleClick += new System.Windows.Forms.MouseEventHandler(this.notifyIconResize_MouseDoubleClick);
			// 
			// btnShowControls
			// 
			this.btnShowControls.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
			this.btnShowControls.Location = new System.Drawing.Point(215, 154);
			this.btnShowControls.Name = "btnShowControls";
			this.btnShowControls.Size = new System.Drawing.Size(126, 33);
			this.btnShowControls.TabIndex = 2;
			this.btnShowControls.Text = "Hide controls";
			this.btnShowControls.UseVisualStyleBackColor = true;
			this.btnShowControls.Click += new System.EventHandler(this.btnShowControls_Click);
			// 
			// cbPin
			// 
			this.cbPin.AutoSize = true;
			this.cbPin.Font = new System.Drawing.Font("Microsoft Sans Serif", 13F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
			this.cbPin.Location = new System.Drawing.Point(142, 157);
			this.cbPin.Name = "cbPin";
			this.cbPin.Size = new System.Drawing.Size(55, 26);
			this.cbPin.TabIndex = 3;
			this.cbPin.Text = "Pin";
			this.cbPin.UseVisualStyleBackColor = true;
			this.cbPin.CheckedChanged += new System.EventHandler(this.cbPin_CheckedChanged);
			// 
			// cbPinBtn
			// 
			this.cbPinBtn.Appearance = System.Windows.Forms.Appearance.Button;
			this.cbPinBtn.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("cbPinBtn.BackgroundImage")));
			this.cbPinBtn.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
			this.cbPinBtn.FlatAppearance.BorderSize = 0;
			this.cbPinBtn.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
			this.cbPinBtn.Location = new System.Drawing.Point(313, 9);
			this.cbPinBtn.Name = "cbPinBtn";
			this.cbPinBtn.Size = new System.Drawing.Size(25, 25);
			this.cbPinBtn.TabIndex = 4;
			this.cbPinBtn.UseVisualStyleBackColor = true;
			this.cbPinBtn.CheckedChanged += new System.EventHandler(this.cbPinBtn_CheckedChanged);
			// 
			// axPlayer
			// 
			this.axPlayer.Enabled = true;
			this.axPlayer.Location = new System.Drawing.Point(51, 104);
			this.axPlayer.Name = "axPlayer";
			this.axPlayer.OcxState = ((System.Windows.Forms.AxHost.State)(resources.GetObject("axPlayer.OcxState")));
			this.axPlayer.Size = new System.Drawing.Size(233, 44);
			this.axPlayer.TabIndex = 5;
			this.axPlayer.Visible = false;
			// 
			// startOnStartupToolStripMenuItem
			// 
			this.startOnStartupToolStripMenuItem.Name = "startOnStartupToolStripMenuItem";
			this.startOnStartupToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
			this.startOnStartupToolStripMenuItem.Text = "Start on startup";
			this.startOnStartupToolStripMenuItem.Click += new System.EventHandler(this.startOnStartupToolStripMenuItem_Click);
			// 
			// MainForm
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.BackColor = System.Drawing.SystemColors.Control;
			this.ClientSize = new System.Drawing.Size(351, 204);
			this.Controls.Add(this.axPlayer);
			this.Controls.Add(this.cbPinBtn);
			this.Controls.Add(this.cbPin);
			this.Controls.Add(this.btnShowControls);
			this.Controls.Add(this.cbShowDate);
			this.Controls.Add(this.labelTime);
			this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
			this.MaximizeBox = false;
			this.Name = "MainForm";
			this.Text = "MainForm";
			this.Resize += new System.EventHandler(this.MainForm_Resize);
			this.contextMenuTray.ResumeLayout(false);
			((System.ComponentModel.ISupportInitialize)(this.axPlayer)).EndInit();
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.Label labelTime;
		private System.Windows.Forms.Timer timer1;
		private System.Windows.Forms.CheckBox cbShowDate;
		private System.Windows.Forms.NotifyIcon notifyIconResize;
		private System.Windows.Forms.Button btnShowControls;
		private System.Windows.Forms.ContextMenuStrip contextMenuTray;
		private System.Windows.Forms.ToolStripMenuItem showControlsToolStripMenuItem;
		private System.Windows.Forms.ToolStripMenuItem showDatToolStripMenuItem;
		private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
		private System.Windows.Forms.ToolStripMenuItem closeToolStripMenuItem;
		private System.Windows.Forms.ToolStripMenuItem colorsToolStripMenuItem;
		private System.Windows.Forms.ToolStripMenuItem backgroundColorToolStripMenuItem;
		private System.Windows.Forms.ToolStripMenuItem foregroundColorToolStripMenuItem;
		private System.Windows.Forms.ToolStripSeparator toolStripSeparator2;
		private System.Windows.Forms.ToolStripMenuItem fontToolStripMenuItem;
		private System.Windows.Forms.ToolStripMenuItem digital7ToolStripMenuItem;
		private System.Windows.Forms.ToolStripMenuItem systemFontsToolStripMenuItem;
		private System.Windows.Forms.ToolStripMenuItem iconToolStripMenuItem;
		private System.Windows.Forms.CheckBox cbPin;
		private System.Windows.Forms.CheckBox cbPinBtn;
		private System.Windows.Forms.ToolStripSeparator toolStripSeparator3;
		private System.Windows.Forms.ToolStripMenuItem alarmToolStripMenuItem;
		private AxWMPLib.AxWindowsMediaPlayer axPlayer;
		private System.Windows.Forms.ToolStripMenuItem startOnStartupToolStripMenuItem;
	}
}

