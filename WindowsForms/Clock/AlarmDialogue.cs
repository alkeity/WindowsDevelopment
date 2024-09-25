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

		public DateTime AlarmTime
		{
			get => alarmTime;
		}
		public AlarmDialogue()
		{
			InitializeComponent();
			alarmTime = DateTime.Now;
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
	}
}
