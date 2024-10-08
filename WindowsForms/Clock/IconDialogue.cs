﻿using System;
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
	public partial class IconDialogue : Form // girl you're BLIND TODO try to use CommonDialogue
	{
		int itemIndex;

		public int ItemIndex
		{
			get => itemIndex;
		}

		private void SetIcon()
		{
			switch (Properties.Settings.Default.IconIndex)
			{
				case 0:
					this.Icon = Properties.Resources.icon_default;
					break;
				case 1:
					this.Icon = Properties.Resources.icon_blue_clock;
					break;
			}
		}
		public IconDialogue()
		{
			InitializeComponent();
			SetIcon();
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
