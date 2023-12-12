using System;
using System.Collections.Generic;
using System.Windows.Forms;
using System.Threading;

namespace WorldClockApp
{
    public partial class Form1 : Form
    {
        private Dictionary<string, (int, string)> timeDiff = new Dictionary<string, (int, string)>()
        {
            // 여기에 시차와 표준시를 입력해주세요.
        };

        public Form1()
        {
            InitializeComponent();
            InitializeClocks();
            UpdateTimes();
        }

        private void InitializeClocks()
        {
            int idx = 0;
            foreach (var city in timeDiff.Keys)
            {
                var label = new Label();
                label.AutoSize = true;
                label.Font = new System.Drawing.Font("Arial", 9);
                label.Location = new System.Drawing.Point(20, 5 + idx * 30);
                label.Name = $"label{idx}";
                label.Text = $"{city}: {GetLocalTime(city)}";
                Controls.Add(label);
                idx++;
            }
        }

        private string GetLocalTime(string city)
        {
            var cityTimeDiff = timeDiff[city].Item1;
            var cityStandardTime = timeDiff[city].Item2;
            var currentUtcTime = DateTime.UtcNow;
            var localTime = currentUtcTime.AddHours(cityTimeDiff);
            return localTime.ToString($"{cityStandardTime} (yyyy) (MM) (dd) (HH) (mm) (ss)");
        }

        private void UpdateTimes()
        {
            while (true)
            {
                Thread.Sleep(1000);
                foreach (var city in timeDiff.Keys)
                {
                    Controls[$"label{GetIndexOfCity(city)}"].Text = $"{city}: {GetLocalTime(city)}";
                }
            }
        }

        private int GetIndexOfCity(string city)
        {
            int idx = 0;
            foreach (var key in timeDiff.Keys)
            {
                if (key == city)
                    return idx;
                idx++;
            }
            return -1;
        }
    }
}
