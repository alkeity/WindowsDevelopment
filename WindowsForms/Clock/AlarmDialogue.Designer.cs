namespace Clock
{
	partial class AlarmDialogue
	{
		/// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.IContainer components = null;

		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		/// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
		protected override void Dispose(bool disposing)
		{
			if (disposing && (components != null))
			{
				components.Dispose();
			}
			base.Dispose(disposing);
		}

		#region Windows Form Designer generated code

		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent()
		{
			System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(AlarmDialogue));
			this.dtAlarmPicker = new System.Windows.Forms.DateTimePicker();
			this.btnOK = new System.Windows.Forms.Button();
			this.btnCancel = new System.Windows.Forms.Button();
			this.btnChooseSound = new System.Windows.Forms.Button();
			this.SuspendLayout();
			// 
			// dtAlarmPicker
			// 
			this.dtAlarmPicker.CalendarFont = new System.Drawing.Font("Microsoft Sans Serif", 24F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
			this.dtAlarmPicker.Font = new System.Drawing.Font("Microsoft Sans Serif", 24F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
			this.dtAlarmPicker.Format = System.Windows.Forms.DateTimePickerFormat.Time;
			this.dtAlarmPicker.Location = new System.Drawing.Point(72, 12);
			this.dtAlarmPicker.Name = "dtAlarmPicker";
			this.dtAlarmPicker.ShowUpDown = true;
			this.dtAlarmPicker.Size = new System.Drawing.Size(200, 44);
			this.dtAlarmPicker.TabIndex = 0;
			// 
			// btnOK
			// 
			this.btnOK.DialogResult = System.Windows.Forms.DialogResult.OK;
			this.btnOK.Location = new System.Drawing.Point(175, 78);
			this.btnOK.Name = "btnOK";
			this.btnOK.Size = new System.Drawing.Size(75, 23);
			this.btnOK.TabIndex = 1;
			this.btnOK.Text = "OK";
			this.btnOK.UseVisualStyleBackColor = true;
			this.btnOK.Click += new System.EventHandler(this.btnOK_Click);
			// 
			// btnCancel
			// 
			this.btnCancel.DialogResult = System.Windows.Forms.DialogResult.Cancel;
			this.btnCancel.Location = new System.Drawing.Point(256, 78);
			this.btnCancel.Name = "btnCancel";
			this.btnCancel.Size = new System.Drawing.Size(75, 23);
			this.btnCancel.TabIndex = 2;
			this.btnCancel.Text = "Cancel";
			this.btnCancel.UseVisualStyleBackColor = true;
			this.btnCancel.Click += new System.EventHandler(this.btnCancel_Click);
			// 
			// btnChooseSound
			// 
			this.btnChooseSound.Location = new System.Drawing.Point(12, 80);
			this.btnChooseSound.Name = "btnChooseSound";
			this.btnChooseSound.Size = new System.Drawing.Size(75, 23);
			this.btnChooseSound.TabIndex = 3;
			this.btnChooseSound.Text = "Alarm sound";
			this.btnChooseSound.UseVisualStyleBackColor = true;
			this.btnChooseSound.Click += new System.EventHandler(this.btnChooseSound_Click);
			// 
			// AlarmDialogue
			// 
			this.AcceptButton = this.btnOK;
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.None;
			this.CancelButton = this.btnCancel;
			this.ClientSize = new System.Drawing.Size(344, 113);
			this.Controls.Add(this.btnChooseSound);
			this.Controls.Add(this.btnCancel);
			this.Controls.Add(this.btnOK);
			this.Controls.Add(this.dtAlarmPicker);
			this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
			this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
			this.MaximizeBox = false;
			this.MinimizeBox = false;
			this.Name = "AlarmDialogue";
			this.ShowInTaskbar = false;
			this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
			this.Text = "AlarmForm";
			this.TopMost = true;
			this.ResumeLayout(false);

		}

		#endregion

		private System.Windows.Forms.DateTimePicker dtAlarmPicker;
		private System.Windows.Forms.Button btnOK;
		private System.Windows.Forms.Button btnCancel;
		private System.Windows.Forms.Button btnChooseSound;
	}
}