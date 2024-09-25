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
	public partial class IconDialogue : Form
	{
		int itemIndex;

		public int ItemIndex
		{
			get => itemIndex;
		}
		public IconDialogue()
		{
			InitializeComponent();
			itemIndex = 0;
		}

		private void btnOK_Click(object sender, EventArgs e)
		{
			DialogResult = DialogResult.OK;
			itemIndex = lvIcons.SelectedItems[0].Index;
		}

		private void btnCancel_Click(object sender, EventArgs e)
		{
			DialogResult = DialogResult.Cancel;
		}
	}
}
