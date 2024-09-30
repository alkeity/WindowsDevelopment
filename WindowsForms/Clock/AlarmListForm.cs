using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

// currently alarm list does not updates if alarm goes off while this window is open

namespace Clock
{
	public partial class AlarmListForm : Form
	{
		MainForm owner;
		public AlarmListForm(MainForm owner)
		{
			InitializeComponent();
			this.owner = owner;
			this.Icon = owner.Icon;
			if (owner.AlarmList.Count > 0)
			{
				FillAlarmList();
				lbAlarms.SetSelected(0, true);
			}
		}

		private void FillAlarmList()
		{
			for (int i = 0; i < owner.AlarmList.Count; i++) lbAlarms.Items.Add(owner.AlarmList[i]);
		}

		private void btnAdd_Click(object sender, EventArgs e)
		{
			AlarmDialogue alarmDialogue = new AlarmDialogue();
			if (alarmDialogue.ShowDialog() == DialogResult.OK)
			{
				Alarm temp = alarmDialogue.Alarm;
				Console.WriteLine(lbAlarms.Items.Contains(temp));
				Console.WriteLine("loop:");
				foreach (var item in lbAlarms.Items) Console.WriteLine(item.Equals(temp));
				if (owner.AddAlarmToList(alarmDialogue.Alarm)) lbAlarms.Items.Add((Alarm)alarmDialogue.Alarm);
			}
			lbAlarms.SetSelected(lbAlarms.Items.Count - 1, true);
		}

		private void btnRemove_Click(object sender, EventArgs e)
		{
			// TODO maybe make Remove button unclickable if list is empty?
			if (lbAlarms.SelectedIndex >= 0)
			{
				owner.RemoveAlarmFromList(lbAlarms.SelectedIndex);
				lbAlarms.Items.RemoveAt(lbAlarms.SelectedIndex);
				if (lbAlarms.Items.Count > 0) lbAlarms.SetSelected(0, true);
			}
			else MessageBox.Show("Nothing selected", "Error", MessageBoxButtons.OK, MessageBoxIcon.Warning);
		}
	}
}
