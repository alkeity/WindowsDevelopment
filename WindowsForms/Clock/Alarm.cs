using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Clock
{
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

		public override string ToString()
		{
			return $"{alarmTime}, {soundPath.Split('\\').Last()}";
		}
	}
}
