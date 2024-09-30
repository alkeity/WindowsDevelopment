using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Clock
{
	public class Alarm : object, IComparable, IEquatable<Alarm>
	{
		DateTime alarmTime;
		string soundPath;

		public DateTime AlarmTime
		{
			get => alarmTime;
			set
			{
				if (DateTime.Now < value)
				{
					DateTime temp = value;
					alarmTime = temp.Date + new TimeSpan(temp.TimeOfDay.Hours, temp.TimeOfDay.Minutes, 0);
				}
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
			DateTime temp = DateTime.Now;
			alarmTime = temp.Date + new TimeSpan(temp.TimeOfDay.Hours, temp.TimeOfDay.Minutes, 0);
			soundPath = string.Empty;
		}

		public int CompareTo(object obj)
		{
			return alarmTime.CompareTo((obj as Alarm).AlarmTime);
		}

		public bool Equals(Alarm other)
		{
			return alarmTime.Equals(other.alarmTime);
		}

		public override string ToString()
		{
			return $"{alarmTime}, {soundPath.Split('\\').Last()}";
		}
	}
}
