using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Configuration;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Net;
using System.Net.NetworkInformation;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace PCNanny
{
    public partial class Form1 : Form
    {
        private WebClient webclient;

        public Form1()
        {
            InitializeComponent();
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            Temperature1.Text = GetTemperature("Server01");
            Temperature2.Text = GetTemperature("Server02");
            Temperature3.Text = GetTemperature("Server03");
            Temperature4.Text = GetTemperature("Server04");
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            ip1.Text = ConfigurationManager.AppSettings["Server01"].Replace("http://", string.Empty);
            ip2.Text = ConfigurationManager.AppSettings["Server02"].Replace("http://", string.Empty);
            ip3.Text = ConfigurationManager.AppSettings["Server03"].Replace("http://", string.Empty);
            ip4.Text = ConfigurationManager.AppSettings["Server04"].Replace("http://", string.Empty);

            webclient = new WebClient();
            timer1.Interval = int.Parse(ConfigurationManager.AppSettings["RefreshRateInSeconds"]) * 1000;
            timer1.Start();
        }

        private string GetTemperature(string baseUrl)
        {
            var url = ConfigurationManager.AppSettings[baseUrl];
            if (Ping(url))
                return webclient.DownloadString(new Uri("http://" + url));
            else
                return "?";
        }

        private bool Ping(string ipddress)
        {
            bool ok = true;
            var ping = new Ping();
            var pingReply = ping.Send(ipddress);
            if (pingReply.Status != IPStatus.Success)
            {
                timer1.Stop();
                MessageBox.Show($"Unable to connect to {ipddress}");
                Application.Exit();
                ok = false;
            }
            return ok;
        }

        private void SetArduinoPin(string baseUrl, string cmd)
        {
            var url = ConfigurationManager.AppSettings[baseUrl] ;
            if (Ping(url))
                webclient.DownloadString(new Uri("http://" + url + "/" + cmd));
        }

        private void powerButton1_Click(object sender, EventArgs e)
        {
            SetArduinoPin("Server01", "P");
        }

        private void resetButton1_Click(object sender, EventArgs e)
        {
            SetArduinoPin("Server01", "R");
        }

        private void powerButton2_Click(object sender, EventArgs e)
        {
            SetArduinoPin("Server02", "P");
        }

        private void resetButton2_Click(object sender, EventArgs e)
        {
            SetArduinoPin("Server02", "R");
        }

        private void powerButton3_Click(object sender, EventArgs e)
        {
            SetArduinoPin("Server03", "P");
        }

        private void resetButton3_Click(object sender, EventArgs e)
        {
            SetArduinoPin("Server03", "R");
        }

        private void powerButton4_Click(object sender, EventArgs e)
        {
            SetArduinoPin("Server04", "P");
        }

        private void resetButton4_Click(object sender, EventArgs e)
        {
            SetArduinoPin("Server04", "R");
        }
    }
}
