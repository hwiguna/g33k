using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO.Ports;
using System.Threading.Tasks;

namespace LearnSerialPort
{
    public partial class Form1 : Form
    {
        SerialPort serialPort;

        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            RestoreUserSettings();

            serialPort = new SerialPort(PortTextbox.Text, int.Parse(BaudRateBox.Text));
            serialPort.NewLine = "\r\n"; // CR followed by LF
            //serialPort.DataReceived += new SerialDataReceivedEventHandler(serialPort_DataReceived);
            serialPort.DataReceived += (s,ea) => output.Invoke(new System.Action(() => serialPort_DataReceived(s,ea)));
        }

        private void RestoreUserSettings()
        {
            //-- Restore User Settings --
            PortTextbox.Text = Properties.Settings.Default.comPort;
            FilePathTextbox.Text = Properties.Settings.Default.filePath;
            BaudRateBox.Text = Properties.Settings.Default.baudRate;
            LineDelayTextbox.Text = Properties.Settings.Default.lineDelay;
            LuaFilenameTextbox.Text = Properties.Settings.Default.LuaFilename;
            CommandTextbox.Text = Properties.Settings.Default.Command;
            RunAfterSaving.Checked = Properties.Settings.Default.RunAfterSaving;
        }

        void serialPort_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            SerialPort sp = (SerialPort)sender;
            string indata = sp.ReadExisting();
            //output.Text += "Data Received:\r\n";
            output.Text += indata; // +"\r\n";

            output.SelectionStart = output.Text.Length;
            output.ScrollToCaret();
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (serialPort!=null)
                serialPort.Dispose();
            serialPort = null;

            SaveUserSettings();
        }

        private void SaveUserSettings()
        {
            //-- Save User Settings --
            Properties.Settings.Default.filePath = FilePathTextbox.Text;
            Properties.Settings.Default.comPort = PortTextbox.Text;
            Properties.Settings.Default.baudRate = BaudRateBox.Text;
            Properties.Settings.Default.lineDelay = LineDelayTextbox.Text;
            Properties.Settings.Default.LuaFilename = LuaFilenameTextbox.Text;
            Properties.Settings.Default.Command = CommandTextbox.Text;
            Properties.Settings.Default.RunAfterSaving = RunAfterSaving.Checked;
            Properties.Settings.Default.Save();
        }

        private void Send(string str)
        {
            output.Text += string.Format("SENT: {0}\r\n", str);
            output.SelectionStart = output.Text.Length;
            output.ScrollToCaret();
            serialPort.WriteLine(str);
        }

        private void SendLines(string[] lines)
        {
            Cursor.Current = Cursors.WaitCursor;
            OpenComPort();

            // Send it line by line with small delay to COM port so LUA interpreter on ESP8266 can keep up
            foreach (var line in lines)
            {
                Send(line);
                System.Threading.Thread.Sleep(int.Parse(LineDelayTextbox.Text));
            }

            Cursor.Current = Cursors.Arrow;
        }

        private void SendLines(string multipleLineString)
        {
            string[] lines = multipleLineString.Split(new char[] { '\r', '\n' }, StringSplitOptions.RemoveEmptyEntries);
            SendLines(lines);
        }

        //private void SendLine(string line)
        //{
        //    SendLines(new string[] { line });
        //}

        private void UploadButton_Click(object sender, EventArgs e)
        {
            //Open Text file
            string[] lines = System.IO.File.ReadAllLines(FilePathTextbox.Text);
            SendLines(lines);
        }

        private void ExecuteButton_Click(object sender, EventArgs e)
        {
            //string[] lines = CommandTextbox.Text.Split( new char[] {'\r','\n'}, StringSplitOptions.RemoveEmptyEntries);
            SendLines( CommandTextbox.Text );
        }

        private void OpenComPort()
        {
            if (serialPort.IsOpen) serialPort.Close();
            //-- Keep COM port up-to-date --
            serialPort.PortName = PortTextbox.Text;
            serialPort.BaudRate = int.Parse(BaudRateBox.Text);
            serialPort.Open();
        }

        private void Browse_Click(object sender, EventArgs e)
        {
            DialogResult result = openFileDialog1.ShowDialog();
            if (result == System.Windows.Forms.DialogResult.OK)
            {
                FilePathTextbox.Text = openFileDialog1.FileName;
            }
        }

        private void SaveOnESPButton_Click(object sender, EventArgs e)
        {
            string luaCode = string.Format(
                "file.remove(\"{0}\")\r\n" +
                "file.open(\"{0}\",\"w\")\r\n" +
                "{1}" +
                "file.close()\r\n", LuaFilenameTextbox.Text, WrapInWriteLine(LuaCodeTextbox.Text));

            if (RunAfterSaving.Checked)
            {
                string doFile = string.Format("dofile(\"{0}\")\r\n", LuaFilenameTextbox.Text);
                luaCode += doFile;
                //Array.Resize<string>(ref lines, lines.Length + 1);
                //lines[lines.Length - 1] = doFile;
            }

            SendLines(luaCode);
        }

        private string WrapInWriteLine(string luaCode)
        {
            StringBuilder stringBuilder = new StringBuilder();

            foreach (var line in luaCode.Split(new char[] { '\r', '\n' }, StringSplitOptions.RemoveEmptyEntries))
	        {
                stringBuilder.AppendLine("file.writeline([[" + line + "]])");
	        }

            return stringBuilder.ToString();
        }

        private void RestartButton_Click(object sender, EventArgs e)
        {
            SendLines("node.restart()");
        }

        private void LuaCodeTextbox_keyDown(object sender, KeyEventArgs e)
        {
            if (e.Control & e.KeyCode == Keys.A)
                LuaCodeTextbox.SelectAll();
        }

        private void label2_Click(object sender, EventArgs e)
        {
            string listFiles =
                "l = file.list()\r\n" +
                "for k,v in pairs(l) do\r\n" +
                "  print(\"name:\"..k..\", size:\"..v)\r\n" +
                "end\r\n";

            SendLines(listFiles);
        }

        private void LoadFromESPButton_Click(object sender, EventArgs e)
        {
            string printFileContent =
                "-- Print File Content --\r\n" +
                "filename = '" + LuaFilenameTextbox.Text + "'\r\n" +
                "file.open(filename,'r')\r\n" +
                "txt = ''\r\n" +
                "repeat\r\n" +
                "  line = file.readline()\r\n" +
                "  if (line~=nil) then txt = txt .. line end\r\n" +
                "until line == nil\r\n" +
                "file.close()\r\n" +
                "print(txt)\r\n";

            SendLines(printFileContent);
        }
    }
}
