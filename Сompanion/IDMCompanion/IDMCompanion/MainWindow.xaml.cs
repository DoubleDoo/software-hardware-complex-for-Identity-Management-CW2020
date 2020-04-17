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
using System.Windows.Forms;

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
        private Thread usbThreadAn;
        private SerialPortStream serialPort;
        private int counter = 0;

        public MainWindow()
        {
            InitializeComponent();
            usbbufer = "";
        }

        [STAThread]

        //подключение устройства
        private void Button_Click(object sender, RoutedEventArgs e)
        {
            usbThreadWorking = !usbThreadWorking;
            if (usbThreadWorking)
            {
              
                usbThread = new Thread(new ThreadStart(usbThreadFunk));
                usbThreadAn = new Thread(new ThreadStart(usbThreadAnalys));
                usbThread.Start();
               // System.Threading.Thread.Sleep(50);
                usbThreadAn.Start();
            }
           else
            {
                usbThread.Abort();
                usbThreadAn.Abort();
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
                        this.Dispatcher.Invoke(() => usbbufer += (ch));
                        this.Dispatcher.Invoke(() => dataBox.Text += (ch));

                    }
                }
            }
            
            
                this.Dispatcher.Invoke(() => dataBox.Text = dataBox.Text += "Can not connect to device...\n"); usbThreadWorking = false;
            
        }


        private void usbThreadAnalys()
        {
            /*
            string bufer="";
            while (usbThreadWorking)
            {
                this.Dispatcher.Invoke(() => bufer=usbbufer);
                if (bufer.IndexOf("log:") > 0)
                {
                    this.Dispatcher.Invoke(() => dataBox.Text += "!" + bufer.Substring(bufer.IndexOf("log("), 16) + "!");
                    bufer = "";
                }
                if (bufer.IndexOf("pas:") > 0)
                {
                    this.Dispatcher.Invoke(() => dataBox.Text += "!" + bufer.Substring(bufer.IndexOf("pas("), 16) + "!");
                    bufer = "";
                }
            }*/

            /*
            bool log = false;
            bool pas = false;
            while (usbThreadWorking)
            {
                this.Dispatcher.Invoke(() => 
                {
                    if (dataBox.Text.IndexOf("log:") > 0) log = true;
                });
                this.Dispatcher.Invoke(() =>
                {
                    if (dataBox.Text.IndexOf("pas:") > 0) pas = true;
                });

                if (log)
                    {
                    this.Dispatcher.Invoke(() => dataBox.Text += "1"); //+ usbbufer.Substring(usbbufer.IndexOf("log:"), 16) + "!");
                        usbbufer = "";
                    }
                    else if (pas)
                    {
                        this.Dispatcher.Invoke(() => dataBox.Text += "2"); // + usbbufer.Substring(usbbufer.IndexOf("pas:"), 16) + "!");
                    usbbufer = "";
                    }
                else
                {
                    this.Dispatcher.Invoke(() => dataBox.Text += "");
                }
                
            }*/
            while(true)
            {
                if (usbbufer.Length > 0)
                {
                    System.Threading.Thread.Sleep(100);
                    string login = "";
                    string password = "";
                    bool log = false;
                    bool pas = false;

                    if (usbbufer.IndexOf("l")>=0)
                    {
                        //this.Dispatcher.Invoke(() => dataBox.Text += "!" + usbbufer.Substring(usbbufer.IndexOf("l") + 3, 16) + "!");
                        if (usbbufer[usbbufer.IndexOf("l")+2]=='o'&& usbbufer[usbbufer.IndexOf("l") + 4] == 'g' && usbbufer[usbbufer.IndexOf("l") + 6] == ':')
                        {
                            this.Dispatcher.Invoke(() =>login = usbbufer.Substring(usbbufer.IndexOf("l")+7));
                            log = true;
                            usbbufer = "";
                        }
                        
                    }
                    if (usbbufer.IndexOf("p") >= 0)
                    {
                        if (usbbufer[usbbufer.IndexOf("p") + 2] == 'a' && usbbufer[usbbufer.IndexOf("p") + 4] == 's' && usbbufer[usbbufer.IndexOf("p") + 6] == ':')
                        {
                            this.Dispatcher.Invoke(() => password =  usbbufer.Substring(usbbufer.IndexOf("p") + 7));
                            pas = true;
                            usbbufer = "";
                        }
                    }

                    if (log)
                    {
                        SendKeys.SendWait(login);
                        SendKeys.SendWait("{ENTER}");
                    }

                    if (pas)
                    {
                        byte[] bytes = Encoding.ASCII.GetBytes(password);
                        StringBuilder hex = new StringBuilder(bytes.Length * 2);
                        foreach (byte b in bytes)
                            hex.AppendFormat("{0:x2}", b);
                        password=hex.ToString();
                        SendKeys.SendWait(password);
                        SendKeys.SendWait("{ENTER}");

                        //this.Dispatcher.Invoke(() => dataBox.Text +="|"+ hex.ToString()+"|"); 
                    }
                    // this.Dispatcher.Invoke(() => dataBox.Text += usbbufer.IndexOf("l") + " ");
                    // usbbufer = "";
                }
            }
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
                string inndataBoxstr = inndataBox.Text;
                string data = "";
                if (comandBoxstr.Length>16 || inndataBoxstr.Length > 16)
                {
                    dataBox.Text += ("Too long domen or login" + "\n");
                }
                else
                {
                   
                    while (comandBoxstr.Length < 16) { comandBoxstr += " "; }
                    while (inndataBoxstr.Length < 16) { inndataBoxstr += " "; }
                    data = "N " + inndataBoxstr + comandBoxstr ;
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
