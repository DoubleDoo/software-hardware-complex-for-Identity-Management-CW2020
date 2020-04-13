using RJCP.IO.Ports;
using System;
using System.Collections.Generic;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Threading;
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

namespace IDMCompanion
{
    /// <summary>
    /// Логика взаимодействия для MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private bool usbThreadWorking;
        private Thread usbThread;
        private SerialPortStream serialPort;
        private int counter = 0;

        public MainWindow()
        {
            InitializeComponent();
        }

        [STAThread]
        private void Button_Click(object sender, RoutedEventArgs e)
        {
            usbThreadWorking = !usbThreadWorking;
            if (usbThreadWorking)
            {
              
                usbThread = new Thread(new ThreadStart(usbThreadFunk));
                
                dataBox.Text += ("Connected" + "\n");
                usbThread.Start();
            }
           else
            {
                usbThread.Abort();
                serialPort.Close();
                dataBox.Text += ("Disconnected" + "\n");
            }

        }

        [STAThread]
        private void usbThreadFunk()
        {
            using (serialPort = new SerialPortStream("COM9"))
            {
                serialPort.OpenDirect();

                while (serialPort.IsOpen)
                {
                    char ch = (char)serialPort.ReadChar();
                    this.Dispatcher.Invoke(() => dataBox.Text = dataBox.Text += (ch));
                }
            }
        }


       // private void port_DataReceived(object sender, SerialDataReceivedEventArgs e)
       // {

      //      this.Dispatcher.Invoke(() => dataBox.Text = dataBox.Text += (ReadChar().ReadExisting() + "\n"));
      //  }

        private void Button_Click_1(object sender, RoutedEventArgs e)
        {
            if (usbThreadWorking)
            {
                //usbThread = new Thread(new ThreadStart(usbThreadFunk));

                //dataBox.Text += ("Connected" + "\n");
                //usbThread.Start();
                string data = "(BCDEFGHigklmnopqrstuvwxyz1234567890@!;123456789012345678901234)";
                // counter++;
                serialPort.Write(data);
                dataBox.Text += ("\nОтправлено:" + data+ " \n Получено:");
            }
            else
            {

                dataBox.Text += ("Disconnected, cant send" + "\n");
            }
        }

        private void Button_Click_2(object sender, RoutedEventArgs e)
        {

        }

        private void Button_Click_3(object sender, RoutedEventArgs e)
        {

        }

        private void Button_Click_4(object sender, RoutedEventArgs e)
        {

        }

        private void Button_Click_5(object sender, RoutedEventArgs e)
        {
            if (usbThreadWorking)
            {
                string data = "(BCDEFGHigklmnopqrstuvwxyz1234567890@!;123456789012345678901234)";
                // counter++;
                serialPort.Write(data);
                dataBox.Text += ("\nОтправлено:" + data + " \n Получено:");
            }
            else
            {

                dataBox.Text += ("Disconnected, cant send" + "\n");
            }
        }

        private void Button_Click_6(object sender, RoutedEventArgs e)
        {

        }

        private void Button_Click_7(object sender, RoutedEventArgs e)
        {
            dataBox.Text = "";
        }
    }
}
