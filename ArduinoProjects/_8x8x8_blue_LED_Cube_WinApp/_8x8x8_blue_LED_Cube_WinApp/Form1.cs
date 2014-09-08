using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace _8x8x8_blue_LED_Cube_WinApp
{
    public partial class Form1 : Form
    {
        public SerialPort serialPort;

        public Form1()
        {
            InitializeComponent();
        }

        private void BonkButton_Click(object sender, EventArgs e)
        {
            serialPort.WriteLine("A");
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            string[] portNames = SerialPort.GetPortNames();
            serialPort = new SerialPort(portNames[0], 9600);
            if (serialPort!=null)
            {
                serialPort.DataReceived += serialPort_DataReceived;
                serialPort.Open();
            }

            // Set KeyPreview object to true to allow the form to process  
            // the key before the control with focus processes it. 
            this.KeyPreview = true;
        }

        void serialPort_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            SetText(serialPort.ReadLine());
        }

        private void Form1_Closing(object sender, FormClosingEventArgs e)
        {
            if (serialPort != null) 
                serialPort.Close();
        }

        delegate void SetTextCallback(string text);

        private void SetText(string text)
        {
            // InvokeRequired required compares the thread ID of the
            // calling thread to the thread ID of the creating thread.
            // If these threads are different, it returns true.
            if (this.textBox1.InvokeRequired)
            {
                SetTextCallback d = new SetTextCallback(SetText);
                this.Invoke(d, new object[] { text });
            }
            else
            {
                this.textBox1.Text = text;
            }
        }

        private void Form1_KeyDown(object sender, KeyEventArgs e)
        {
            //e.KeyValue
            serialPort.WriteLine(e.KeyData);
        }
    }
}
