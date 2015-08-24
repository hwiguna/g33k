using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace OcuveraAlertTest
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private SerialPort _serialPort;

        public MainWindow()
        {
            InitializeComponent();
        }

        private void MainWindow_OnLoaded(object sender, RoutedEventArgs e)
        {
            string[] portNames = SerialPort.GetPortNames();
            _serialPort = new SerialPort(portNames[0], 115200);
            _serialPort.DataReceived += (o, args) => StatusTextblock.Dispatcher.Invoke(new System.Action(() =>serialPort_DataReceived(o,args)));
            _serialPort.Open();
            StatusTextblock.Text = "PC Ready!";
        }

        private void TestButton_OnClick(object sender, RoutedEventArgs e)
        {
            string msg = "Go!";
            _serialPort.WriteLine(msg); // Arduino does not care what we send.  Any string will cause it to pulse pin 2
        }


        private void serialPort_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            SerialPort sp = (SerialPort) sender;
            StatusTextblock.Text = DateTime.Now.ToLongTimeString() + " " + sp.ReadExisting();
        }

        private void MainWindow_OnClosing(object sender, CancelEventArgs e)
        {
            if (_serialPort != null && _serialPort.IsOpen) _serialPort.Close();
        }
    }
}
