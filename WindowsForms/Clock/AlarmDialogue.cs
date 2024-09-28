using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
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

	public class Alarm : IComparable
	{
		DateTime alarmTime;
		string soundPath;

		public DateTime AlarmTime
		{
			get => alarmTime;
			set
			{
				if (DateTime.Now < value) alarmTime = value;
				else throw new ArgumentOutOfRangeException($"Can't set alarm in the past. Alarm time: {value}.");
			}
		}

		public string SoundPath
		{
			get => soundPath;
			set
			{
				if (File.Exists(value)) soundPath = value;
				else throw new FileNotFoundException($"File {value} not found.");
			}
		}

		public int CompareTo(object obj)
		{
			return alarmTime.CompareTo((obj as Alarm).AlarmTime);
		}
	}
}
