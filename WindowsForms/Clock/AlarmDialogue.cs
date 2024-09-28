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
}
