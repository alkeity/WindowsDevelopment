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
	public partial class AlarmDialogue : Form
	{
		DateTime alarmTime;
		string soundPath;

		public DateTime AlarmTime { get => alarmTime; }

		public string SoundPath { get => soundPath; }

		public AlarmDialogue()
		{
			InitializeComponent();
			alarmTime = DateTime.Now;
			soundPath = string.Empty;
		}

		private void btnOK_Click(object sender, EventArgs e)
		{
			this.DialogResult = DialogResult.OK;
			alarmTime = dtAlarmPicker.Value;
		}

		private void btnCancel_Click(object sender, EventArgs e)
		{
			this.DialogResult=DialogResult.Cancel;
		}

		private void btnChooseSound_Click(object sender, EventArgs e)
		{
			OpenFileDialog ofd = new OpenFileDialog();
			if (ofd.ShowDialog() == DialogResult.OK) soundPath = ofd.FileName;
		}
	}
}
