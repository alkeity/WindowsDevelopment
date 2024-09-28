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
		Alarm alarm;

		public Alarm Alarm { get => alarm; }

		public AlarmDialogue()
		{
			InitializeComponent();
			alarm = new Alarm();
		}

		private void btnOK_Click(object sender, EventArgs e)
		{
			try
			{
				alarm.AlarmTime = dtAlarmPicker.Value;
				this.DialogResult = DialogResult.OK;
			}
			catch (ArgumentOutOfRangeException ex)
			{
				MessageBox.Show(ex.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Warning);
				this.DialogResult = DialogResult.None;
			}
		}

		private void btnCancel_Click(object sender, EventArgs e)
		{
			this.DialogResult = DialogResult.Cancel;
		}

		private void btnChooseSound_Click(object sender, EventArgs e)
		{
			OpenFileDialog ofd = new OpenFileDialog();
			if (ofd.ShowDialog() == DialogResult.OK) alarm.SoundPath = ofd.FileName;
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

		public Alarm()
		{
			alarmTime = DateTime.Now;
			soundPath = string.Empty;
		}

		public int CompareTo(object obj)
		{
			return alarmTime.CompareTo((obj as Alarm).AlarmTime);
		}
	}
}
