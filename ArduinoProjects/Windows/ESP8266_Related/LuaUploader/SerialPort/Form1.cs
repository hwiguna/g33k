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
using System.IO;

namespace LuaUploader
{
    /// <summary>
    /// Lua Uploader by Hari Wiguna, 2014
    /// 
    /// You can find me at:
    ///     YouTube: https://www.youtube.com/user/hwiguna/videos?view_as=public
    ///     Hackaday.io: http://hackaday.io/projects/hacker/9819
    ///     My blog: http://g33k.blogspot.com/
    ///     Google+: https://plus.google.com/u/0/+HariWiguna/posts
    ///     
    /// "Refresh" icon courtesy of "PC" at iconFinder: https://www.iconfinder.com/icons/59198/refresh_reload_repeat_reset_icon#size=32
    /// </summary>
    public partial class Form1 : Form
    {
        SerialPort serialPort;
        //int StartingLinePosition;
        //bool IsLoadingLua = false;
        DateTime lastSerialActivity = DateTime.MinValue;

        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            RefreshPortList();
            RestoreUserSettings();

            timer1.Stop();
            timer1.Interval = 200;

            serialPort = new SerialPort(PortComboBox.Text, int.Parse(BaudRateBox.Text));
            serialPort.NewLine = "\r\n"; // CR followed by LF
            //serialPort.DataReceived += new SerialDataReceivedEventHandler(serialPort_DataReceived);
            serialPort.DataReceived += (s,ea) => output.Invoke(new System.Action(() => serialPort_DataReceived(s,ea)));
        }

        private void RestoreUserSettings()
        {
            //-- Restore User Settings --
            PortComboBox.Text = Properties.Settings.Default.comPort;
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
            output.SelectionLength = 0;
            output.ScrollToCaret();

            //if (IsLoadingLua)
            //{
            //    output.SelectionStart = StartingLinePosition;
            //    output.SelectionLength = output.TextLength - StartingLinePosition;
            //    //output.Copy();
            //    //LuaCodeTextbox.Clear();
            //    //LuaCodeTextbox.Paste();
            //    Clipboard.Clear();
            //    Clipboard.SetText(output.SelectedText);
            //    LuaCodeTextbox.Clear();
            //    LuaCodeTextbox.Text = Clipboard.GetText();
            //    IsLoadingLua = false;
            //}
            lastSerialActivity = DateTime.Now;
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
            Properties.Settings.Default.comPort = PortComboBox.Text;
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
            string origFile = System.IO.File.ReadAllText(FilePathTextbox.Text);
            string targetFileName = Path.GetFileName(FilePathTextbox.Text);

            string luaCode = string.Format(
                "file.remove(\"{0}\")\r\n" +
                "file.open(\"{0}\",\"w\")\r\n" +
                "{1}" +
                "file.close()\r\n", targetFileName, WrapInWriteLine(origFile));
            
            SendLines(luaCode);
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
            serialPort.PortName = PortComboBox.Text;
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
            //if (e.KeyCode == Keys.F5)
            //{
            //    SendLines(LuaCodeTextbox.SelectedText);
            //    e.Handled = true;
            //}

            if (e.Control)
            {
                switch (e.KeyCode)
                {
                    case Keys.A:
                        LuaCodeTextbox.SelectAll();
                        e.Handled = true;
                        break;
                    case Keys.S:
                        SaveToDisk();
                        e.Handled = true;
                        break;
                }
            }
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

            //IsLoadingLua = true;
            //StartingLinePosition = output.Text.Length + printFileContent.Length; // Pretend as if we've inserted the command. That's where we will start capturing output of the opened file

            SendLines(printFileContent);

            timer1.Start();
        }

        private void ClearOutputButton_Click(object sender, EventArgs e)
        {
            output.Clear();
        }

        private void DeleteButton_Click(object sender, EventArgs e)
        {
            SendLines("file.remove('" + LuaFilenameTextbox.Text + "')");
        }

        private void ListFilesButton_Click(object sender, EventArgs e)
        {
            string listFiles =
                "l = file.list()\r\n" +
                "for k,v in pairs(l) do\r\n" +
                "  print(\"name:\"..k..\", size:\"..v)\r\n" +
                "end\r\n";

            SendLines(listFiles);
        }

        private void RunButton_Click(object sender, EventArgs e)
        {
            string doFile = string.Format("dofile(\"{0}\")\r\n", LuaFilenameTextbox.Text);
            SendLines(doFile);
        }

        private void LoadFromDiskButton_Click(object sender, EventArgs e)
        {
            DialogResult result = openFileDialog1.ShowDialog();
            if (result == System.Windows.Forms.DialogResult.OK)
            {
                LuaCodeTextbox.Text = System.IO.File.ReadAllText(openFileDialog1.FileName);
                LuaFilenameTextbox.Text = Path.GetFileName(openFileDialog1.FileName);
            }
        }

        private void SaveToDiskButton_Click(object sender, EventArgs e)
        {
            SaveToDisk();
        }

        private void SaveToDisk()
        {
            saveFileDialog1.Filter = "LUA|*.lua|Text File|*.txt";
            DialogResult result = saveFileDialog1.ShowDialog();
            if (result == System.Windows.Forms.DialogResult.OK)
            {
                string fileContent = LuaCodeTextbox.Text;
                System.IO.File.WriteAllText(saveFileDialog1.FileName, fileContent);
            }
        }

        private void ExecuteSelectionButton_Click(object sender, EventArgs e)
        {
            SendLines(LuaCodeTextbox.SelectedText);
        }

        private void RefreshButton_Click(object sender, EventArgs e)
        {
            RefreshPortList();
        }

        private void RefreshPortList()
        {
            string[] portNames = SerialPort.GetPortNames();
            PortComboBox.DataSource = portNames;
            PortComboBox.SelectedIndex = portNames.Count() - 1;
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            //Console.WriteLine("TICK");
            if (DateTime.Now.Subtract( lastSerialActivity ).TotalMilliseconds > 500)
            {
                //Console.WriteLine("Haven't received any chars from ESP for a while.  He must be done sending the lua listing...");
                timer1.Stop();
                CopyOutputToCode();
            }
        }

        private void CopyOutputToCode()
        {
            // Thanks to Eskici for the code to find the lua code sent back by the ESP!
            string splitter = "> print(txt)\r\n";

            // making sure that the output contains the splitter
            if (output.Text.Contains(splitter))
            {
                // split the output string and get the latest loaded code
                string spl_code = output.Text.Split(new string[] { splitter }, StringSplitOptions.RemoveEmptyEntries)
                    .ToList<string>().Last<string>().Trim();

                // make sure the code ends with ">" and remove it, other wise something gone wrong, just return empty.
                if (spl_code.EndsWith(">"))
                    LuaCodeTextbox.Text = spl_code.Substring(0, spl_code.Length - 1).Trim();
            }
        }
    }
}
