using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Clock
{
	public partial class MainForm : Form
	{
		bool isVisible;
		String datetimeFormat;

		public MainForm()
		{
			InitializeComponent();
			isVisible = true;
			datetimeFormat = "HH:mm:ss";
		}

		private void MainForm_Load(object sender, EventArgs e)
		{

		}

		private void MainForm_Resize(object sender, EventArgs e)
		{
			if (this.WindowState == FormWindowState.Minimized)
			{
				//notifyIconResize.ShowBalloonTip(500);
				this.ShowInTaskbar = false;
			}
		}

		private void timer1_Tick(object sender, EventArgs e)
		{
			labelTime.Text = DateTime.Now.ToString(datetimeFormat);
		}

		private void checkBox1_CheckedChanged(object sender, EventArgs e)
		{
			showDatToolStripMenuItem.Checked = cbShowDate.Checked;
			if (cbShowDate.Checked) datetimeFormat = "HH:mm:ss\ndd.MM.yyyy";
			else datetimeFormat = "HH:mm:ss";
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

		private void SetControlsVisibility(bool isVisible)
		{
			this.isVisible = isVisible;
			showControlsToolStripMenuItem.Checked = isVisible;

			this.cbShowDate.Visible = isVisible;
			this.btnShowControls.Visible = isVisible;
			this.TopMost = !isVisible;
			this.ShowInTaskbar = isVisible;

			this.TransparencyKey = isVisible ? Color.Empty : this.BackColor;
			this.FormBorderStyle = isVisible ? FormBorderStyle.Sizable : FormBorderStyle.None;
			labelTime.BackColor = isVisible ? this.BackColor : Color.LightGray;
		}
	}
}
