using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace _8x8x8_blue_LED_Cube_WinApp
{
    public partial class Form1 : Form
    {
        private const int baudRate = 19200;

        public SerialPort serialPort;

        bool[,,] cube = new bool[8,8,8];
        
        public Form1()
        {
            InitializeComponent();
        }

        private string CubeToString()
        {
            string cubeAsString = "";

            for (int x = 0; x < 8; x++)
            {
                for (int y = 0; y < 8; y++)
                {
                    for (int z = 0; z < 8; z++)
                    {
                        cubeAsString += cube[x, y, z] ? "*" : ".";
                    }
                }
            }
            return cubeAsString;
        }

        void InitCube()
        {
            for (int x = 0; x < 8; x++)
            {
                for (int y = 0; y < 8; y++)
                {
                    for (int z = 0; z < 8; z++)
                    {
                        cube[x, y, z] = false;
                    }
                }
            }
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            InitCube();

            string[] portNames = SerialPort.GetPortNames();
            textBox1.Text += "Port: " + portNames[0] + Environment.NewLine;
            serialPort = new SerialPort(portNames[0], baudRate);
            if (serialPort!=null)
            {
                //serialPort.Handshake = Handshake.XOnXOff;
                serialPort.DataReceived += serialPort_DataReceived;
                serialPort.Open();
            }

            // Set KeyPreview object to true to allow the form to process  
            // the key before the control with focus processes it. 
            this.KeyPreview = true;
        }

        void serialPort_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            //SetText(serialPort.ReadLine() + Environment.NewLine);
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
                this.textBox1.Text += text;
            }
        }

        private void Form1_KeyDown(object sender, KeyEventArgs e)
        {
            //e.KeyValue
            //serialPort.WriteLine(e.KeyData);
        }


        private void BonkButton_Click(object sender, EventArgs e)
        {
            cube[0,0,7] = true;
            SendCube();
            //byte[] cube64 = new byte[64];
            //byte[,] cubeArr = new byte[8,8];
            //cubeArr[0, 7] = 128;
            //int idx = 0;
            //for (int y = 0; y < 8; y++)
            //{
            //    for (int z = 0; z < 8; z++)
            //    {
            //        cube64[idx++] = cubeArr[y, z];
            //    }   
            //}
            //serialPort.Write(cube64, 0, 64);                    
        }

        private void OffButton_Click(object sender, EventArgs e)
        {
            cube[0,0,7] = false;
            SendCube();
            //byte[] cube64 = new byte[64];
            //byte[,] cubeArr = new byte[8, 8];
            //cubeArr[0, 0] = 0;
            //int idx = 0;
            //for (int y = 0; y < 8; y++)
            //{
            //    for (int z = 0; z < 8; z++)
            //    {
            //        cube64[idx++] = cubeArr[y, z];
            //    }
            //}
            //serialPort.Write(cube64, 0, 64);

            //cube[0, 0, 7] = false;
            ////serialPort.WriteLine(CubeToString());
            //string str512 = CubeToString();
            //serialPort.WriteLine(str512.Substring(0,128));
            //serialPort.WriteLine(str512.Substring(128,128));
            //serialPort.WriteLine(str512.Substring(256, 128));
            //serialPort.WriteLine(str512.Substring(384, 128));
        }

        private void SendCube()
        {
            int idx = 0;
            byte[] cube64 = new byte[64];
            for (int y = 0; y < 8; y++)
            {
                for (int z = 0; z < 8; z++)
                {
                    int xBits = 0;
                    for (int x = 0; x < 8; x++)
                    {
                        xBits = (xBits << 1) | (cube[x, y, z] ? 1 : 0);
                    }
                    cube64[idx++] = (byte)xBits;
                }
            }
            serialPort.Write(cube64, 0, 64);
        }

        private void AnimateBtn_Click(object sender, EventArgs e)
        {
            for (int z = 0; z < 8; z++)
            {
                for (int i = 0; i < 4; i++)
                    cube[i, 0, z] = true;
                SendCube();

                Thread.Sleep(1000);

                for (int i = 0; i < 4; i++)
                    cube[i, 0, z] = false;
                SendCube();

                Thread.Sleep(100);
            }
        }
    }
}
