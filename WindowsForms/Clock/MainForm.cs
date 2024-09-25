//#define CONSOLE

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Drawing.Text;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using static System.Windows.Forms.VisualStyles.VisualStyleElement;
using static System.Windows.Forms.VisualStyles.VisualStyleElement.Window;

namespace Clock
{
	public partial class MainForm : Form
	{
		bool isVisible;
		int boundsX = 25;
		int boundsY = 75;
		String datetimeFormat;
		String soundPath;
		DateTime alarmTime;
		PrivateFontCollection fontCollection;

		private Point GetPosition()
		{
			int startX = System.Windows.Forms.Screen.PrimaryScreen.Bounds.Right - this.Right - boundsX;
			int startY = System.Windows.Forms.Screen.PrimaryScreen.Bounds.Top + boundsY;

			return new Point(startX, startY);
		}

		private void SetControlsVisibility(bool isVisible)
		{
			this.isVisible = isVisible;
			showControlsToolStripMenuItem.Checked = isVisible;

			this.cbShowDate.Visible = isVisible;
			this.cbPin.Visible = isVisible;
			this.cbPinBtn.Visible = isVisible;
			this.btnShowControls.Visible = isVisible;
			this.TopMost = isVisible && !cbPin.Checked ? false : true;
			this.ShowInTaskbar = isVisible;

			this.TransparencyKey = isVisible ? Color.Empty : this.BackColor;
			this.FormBorderStyle = isVisible ? FormBorderStyle.Sizable : FormBorderStyle.None;
			labelTime.BackColor = isVisible ? this.BackColor : Color.LightGray;
		}

		private void SetCustomFont()
		{
			labelTime.Font = new Font(fontCollection.Families[0], 50, FontStyle.Regular);
			Properties.Settings.Default.isCustomFont = true;
			Properties.Settings.Default.Save();
		}

		private void SetIcon()
		{
			switch (Properties.Settings.Default.IconIndex)
			{
				case 0:
					this.Icon = Properties.Resources.icon_default;
					notifyIconResize.Icon = Properties.Resources.icon_default;
					break;
				case 1:
					this.Icon = Properties.Resources.icon_blue_clock;
					notifyIconResize.Icon = Properties.Resources.icon_blue_clock;
					break;
			}
		}

		public MainForm()
		{
#if CONSOLE
			AllocConsole();
#endif
			InitializeComponent();

			fontCollection = new PrivateFontCollection();
			fontCollection.AddFontFile("..\\..\\Resources\\digital-7.ttf");

			isVisible = true;
			datetimeFormat = "HH:mm:ss";
			this.StartPosition = FormStartPosition.Manual;
			this.Location = GetPosition();
			this.BackColor = Properties.Settings.Default.BackgroundColor;
			this.ForeColor = Properties.Settings.Default.ForegroundColor;
			SetIcon();

			labelTime.BackColor = Properties.Settings.Default.BackgroundColor;
			labelTime.ForeColor = Properties.Settings.Default.ForegroundColor;
			if (Properties.Settings.Default.isCustomFont) SetCustomFont();
			else labelTime.Font = Properties.Settings.Default.ClockFont;
		}

		~MainForm()
		{
			fontCollection.Dispose();
#if CONSOLE
			FreeConsole();
#endif
		}

		private void MainForm_Resize(object sender, EventArgs e)
		{
			if (this.WindowState == FormWindowState.Minimized) this.ShowInTaskbar = false;
			else if (isVisible) SetControlsVisibility(true);
		}

		private void timer1_Tick(object sender, EventArgs e)
		{
			DateTime timeNow = new DateTime(DateTime.Now.Ticks - DateTime.Now.Ticks % TimeSpan.TicksPerSecond);
			labelTime.Text = DateTime.Now.ToString(datetimeFormat);
			if (alarmTime.Equals(timeNow))
			{
				if (soundPath != string.Empty)
				{
					axPlayer.URL = soundPath;
					axPlayer.Ctlcontrols.play();
				}
				MessageBox.Show("Get uppppp");
				notifyIconResize.Text = "Clock";
			}
		}

		private void labelTime_DoubleClick(object sender, EventArgs e)
		{
			SetControlsVisibility(!isVisible);
		}

		private void checkBox1_CheckedChanged(object sender, EventArgs e)
		{
			showDatToolStripMenuItem.Checked = cbShowDate.Checked;
			if (cbShowDate.Checked) datetimeFormat = "HH:mm:ss\ndd.MM.yyyy";
			else datetimeFormat = "HH:mm:ss";
		}

		private void cbPinBtn_CheckedChanged(object sender, EventArgs e)
		{
			this.TopMost = cbPinBtn.Checked;
			cbPin.Checked = cbPinBtn.Checked;
			cbPinBtn.BackgroundImage = cbPinBtn.Checked ? Properties.Resources.pin_fill.ToBitmap()
				: Properties.Resources.pin_outline.ToBitmap();
		}

		private void cbPin_CheckedChanged(object sender, EventArgs e)
		{
			this.TopMost = cbPin.Checked;
			cbPinBtn.Checked = cbPin.Checked;
		}

		private void notifyIconResize_MouseDoubleClick(object sender, MouseEventArgs e)
		{
			SetControlsVisibility(true);
			this.Show();
			this.WindowState = FormWindowState.Normal;
		}

		private void btnShowControls_Click(object sender, EventArgs e)
		{
			SetControlsVisibility(false);
		}

		private void showControlsToolStripMenuItem_Click(object sender, EventArgs e)
		{
			SetControlsVisibility(!isVisible);
		}

		private void showDatToolStripMenuItem_Click(object sender, EventArgs e)
		{
			cbShowDate.Checked = !cbShowDate.Checked;
			showDatToolStripMenuItem.Checked = cbShowDate.Checked;
		}

		private void closeToolStripMenuItem_Click(object sender, EventArgs e)
		{
			this.Close();
		}

		private void backgroundColorToolStripMenuItem_Click(object sender, EventArgs e)
		{
			ColorDialog dialog = new ColorDialog();
			if (dialog.ShowDialog() == DialogResult.OK)
			{
				labelTime.BackColor = dialog.Color;
				this.BackColor = dialog.Color;
				Properties.Settings.Default.BackgroundColor = dialog.Color;
				Properties.Settings.Default.Save();
			}
		}

		private void foregroundColorToolStripMenuItem_Click(object sender, EventArgs e)
		{
			ColorDialog dialog = new ColorDialog();
			if (dialog.ShowDialog() == DialogResult.OK)
			{
				labelTime.ForeColor = dialog.Color;
				this.ForeColor = dialog.Color;
				Properties.Settings.Default.ForegroundColor = dialog.Color;
				Properties.Settings.Default.Save();
			}
		}

		private void digital7ToolStripMenuItem_Click(object sender, EventArgs e)
		{
			SetCustomFont();
		}

		private void systemFontsToolStripMenuItem_Click(object sender, EventArgs e)
		{
			FontDialog dialog = new FontDialog();
			if (dialog.ShowDialog() == DialogResult.OK)
			{
				labelTime.Font = dialog.Font;
				Properties.Settings.Default.ClockFont = dialog.Font;
				Properties.Settings.Default.isCustomFont = false;
				Properties.Settings.Default.Save();
			}
		}

		private void iconToolStripMenuItem_Click(object sender, EventArgs e)
		{
			IconDialogue dialog = new IconDialogue();
			if (dialog.ShowDialog() == DialogResult.OK)
			{
				Properties.Settings.Default.IconIndex = dialog.ItemIndex;
				Properties.Settings.Default.Save();
				SetIcon();
			}
		}

		private void alarmToolStripMenuItem_Click(object sender, EventArgs e)
		{
			AlarmDialogue alarmForm = new AlarmDialogue();
			if (alarmForm.ShowDialog() == DialogResult.OK)
			{
				alarmTime = alarmForm.AlarmTime;
				soundPath = alarmForm.SoundPath;
				notifyIconResize.Text = $"Alarm time: {alarmTime}";
			}
		}

		[DllImport("kernel32.dll")]
		private static extern bool AllocConsole();
		[DllImport("kernel32.dll")]
		private static extern bool FreeConsole();
	}
}
