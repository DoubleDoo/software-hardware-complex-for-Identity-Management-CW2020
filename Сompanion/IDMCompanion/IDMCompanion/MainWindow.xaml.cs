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
using System.Management;
using System.Collections.Generic;
using System.Security.Cryptography;
using System.Text;

namespace IDMCompanion
{
    /// <summary>
    /// Логика взаимодействия для MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private bool usbThreadWorking;
        private string usbbufer;
        private Thread usbThread;
        private SerialPortStream serialPort;
        private int counter = 0;

        public MainWindow()
        {
            InitializeComponent();
        }

        [STAThread]

        //подключение устройства
        private void Button_Click(object sender, RoutedEventArgs e)
        {
            usbThreadWorking = !usbThreadWorking;
            if (usbThreadWorking)
            {
              
                usbThread = new Thread(new ThreadStart(usbThreadFunk));
                
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
            if (SerialPortStream.GetPortNames().Length > 0)
            {
                this.Dispatcher.Invoke(() => dataBox.Text += ("Connected" + "\n"));
                
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
            
            
                this.Dispatcher.Invoke(() => dataBox.Text = dataBox.Text += "Can not connect to device...\n"); usbThreadWorking = false;
            
        }


       // private void port_DataReceived(object sender, SerialDataReceivedEventArgs e)
       // {

      //      this.Dispatcher.Invoke(() => dataBox.Text = dataBox.Text += (ReadChar().ReadExisting() + "\n"));
      //  }



         //отправка данных
        private void Button_Click_1(object sender, RoutedEventArgs e)
        {
            if (usbThreadWorking)
            {
                //comandBox
                //inndataBox
                string comandBoxstr = comandBox.Text;
                string inndataBoxstr = comandBox.Text;
                string data = "";
                if (comandBoxstr.Length>16 || inndataBoxstr.Length > 16)
                {
                    dataBox.Text += ("Too long domen or login" + "\n");
                }
                else
                {
                   
                    while (comandBoxstr.Length < 16) { comandBoxstr += " "; }
                    while (inndataBoxstr.Length < 16) { inndataBoxstr += " "; }
                    data = "N " + comandBoxstr + inndataBoxstr;
                    while (data.Length < 64) { data += " "; }
                }
                serialPort.Write(data);
                dataBox.Text += ("\nОтправлено:" + data+ " \n Получено:");
            }
            else
            {

                dataBox.Text += ("Disconnected, cant send" + "\n");
            }
            
        }

        //начать инициацию
        private void Button_Click_2(object sender, RoutedEventArgs e)
        {
            if (usbThreadWorking)
            {
                string data = "P " + GetMD5OFIDs();
                serialPort.Write(data);
                dataBox.Text += ("\nОтправлено: " + "Init comand " + " \n Получено:");
            }
            else
            {

                dataBox.Text += ("Disconnected, cant send" + "\n");
            }
        }

        //импорт
        private void Button_Click_3(object sender, RoutedEventArgs e)
        {
            if (usbThreadWorking)
            {
                string data = "I";
                serialPort.Write(data);
                dataBox.Text += ("\nОтправлено: " + "Get all data command" + " \n Получено:");
            }
            else
            {
                dataBox.Text += ("Disconnected, cant send" + "\n");
            }
        }

        //сброс устройства
        private void Button_Click_4(object sender, RoutedEventArgs e)
        {
            if (usbThreadWorking)
            {
                string data = "C";
                serialPort.Write(data);
                dataBox.Text += ("\nОтправлено: " + "Clear comand " + " \n Получено:");
            }
            else
            {
                dataBox.Text += ("Disconnected, cant send" + "\n");
            }
        }

        //Добавить новый надежный ПК
        private void Button_Click_5(object sender, RoutedEventArgs e)
        {
            if (usbThreadWorking)
            {
                string data = "A";
                serialPort.Write(data);
                dataBox.Text += ("\nОтправлено: " + "Add safe PC comand " + " \n Получено:");
            }
            else
            {
                dataBox.Text += ("Disconnected, cant send" + "\n");
            }
        }
        
        //Восстановление
        private void Button_Click_6(object sender, RoutedEventArgs e)
        {
            dataBox.Text += ("\n Команда не предусмотрена \n");
        }

        private void Button_Click_7(object sender, RoutedEventArgs e)
        {
            dataBox.Text = "";
        }



         public string GetMD5OFIDs()
            {
                Dictionary<string, string> ids =
               new Dictionary<string, string>();

                ManagementObjectSearcher searcher;

                //процессор
                searcher = new ManagementObjectSearcher("root\\CIMV2",
                       "SELECT * FROM Win32_Processor");
                foreach (ManagementObject queryObj in searcher.Get())
                    ids.Add("ProcessorId", queryObj["ProcessorId"].ToString());

                //мать
                searcher = new ManagementObjectSearcher("root\\CIMV2",
                       "SELECT * FROM CIM_Card");
                foreach (ManagementObject queryObj in searcher.Get())
                    ids.Add("CardID", queryObj["SerialNumber"].ToString());
                //UUID
                searcher = new ManagementObjectSearcher("root\\CIMV2",
                       "SELECT UUID FROM Win32_ComputerSystemProduct");
                foreach (ManagementObject queryObj in searcher.Get())
                    ids.Add("UUID", queryObj["UUID"].ToString());

                string outp = "";
                foreach (var x in ids)
                    outp += x.Value;
                var md5 = MD5.Create();
                var hash = md5.ComputeHash(Encoding.UTF8.GetBytes(outp));

                return Convert.ToBase64String(hash);
            
            }

        private void comandBox_TextChanged(object sender, TextChangedEventArgs e)
        {

        }
    }
}
