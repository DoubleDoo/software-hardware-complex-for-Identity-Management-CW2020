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
using System.IO;

namespace IDMCompanion
{
    /// <summary>
    /// Логика взаимодействия для MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private bool usbThreadWorking;
        private string usbbufer;
        private string naeedTotransfer;
        private Thread usbThread;
        private Thread usbThreadAn;
        private Thread datatransfer;
        private SerialPortStream serialPort;
        private int counter = 0;
        private string login = "";
        private string password = "";
        bool naeedTotransfercheck;

        public MainWindow()
        {
            InitializeComponent();
            usbbufer = ""; naeedTotransfer = "";
            usbThread = new Thread(new ThreadStart(usbThreadFunk));
            usbThreadAn = new Thread(new ThreadStart(usbThreadAnalys));
            datatransfer = new Thread(new ThreadStart(traansferdata));
            usbThread.Start();
            usbThreadAn.Start();
            datatransfer.Start();
        }

     
        //подключение устройства
        /*
        private void Button_Click(object sender, RoutedEventArgs e)
        {
            usbThreadWorking = !usbThreadWorking;
            if (usbThreadWorking)
            {
                usbbufer = "";
                usbThread = new Thread(new ThreadStart(usbThreadFunk));
                usbThreadAn = new Thread(new ThreadStart(usbThreadAnalys));
                datatransfer = new Thread(new ThreadStart(traansferdata));
                usbThread.Start();
                usbThreadAn.Start();
                datatransfer.Start();
            }
            else
            {
                usbThread.Abort();
                usbThreadAn.Abort();
                datatransfer.Abort();
                serialPort.Close();
                dataBox.Text += ("Disconnected" + "\n");
                usbbufer = "";

            }

        }*/

        [STAThread]
        private void usbThreadFunk()
        {
            while (true)
            {
                if (SerialPortStream.GetPortNames().Length > 0)
                {
                    foreach (string name in SerialPortStream.GetPortNames())
                    {
                        try
                        {
                            using (serialPort = new SerialPortStream(name))
                            {
                                serialPort.OpenDirect();
                                //string data = "P " + GetMD5OFIDs();
                                //string data = "P 123456789012345678901234";
                                string data = "P 098765432109876543211234";
                                //string data = "P 0987654321dddd6543211234";
                                //string data = "P 1187654321ddgd6543211234";
                                //data = data.Insert(5, "s");/////
                                serialPort.Write(data);
                                this.Dispatcher.Invoke(() => dataBox.Text = dataBox.Text += "Wait...\n");
                                //System.Threading.Thread.Sleep(100);
                                int i = 0;
                                char a, b;
                                a = (char)serialPort.ReadChar();
                                b = (char)serialPort.ReadChar();
                                if (a == 'O' && b == 'K') this.Dispatcher.Invoke(() => dataBox.Text = dataBox.Text += "Connected\n");
                                else if (a == 'N' && b == 'O')
                                {
                                    this.Dispatcher.Invoke(() => dataBox.Text += ("Your PC is unsaved or you didn't connect the device" + "\n"));
                                }
                                else
                                {
                                   // this.Dispatcher.Invoke(() => dataBox.Text += ("Something  wrong..." + "\n"));
                                }
                                usbThreadWorking = true;
                                while (serialPort.IsOpen)
                                {
                                    char ch = (char)serialPort.ReadChar();
                                    this.Dispatcher.Invoke(() => usbbufer += (ch));
                                    this.Dispatcher.Invoke(() => dataBox.Text += (ch));
                                    this.Dispatcher.Invoke(() => dataBox.ScrollToEnd());
                                    //this.Dispatcher.Invoke(() => labelcount.Content= usbbufer.Length);
                                    
                                }
                            }

                        }
                        catch { }
                    }
                    this.Dispatcher.Invoke(() => dataBox.Text = dataBox.Text += "No device found\n");
                    System.Threading.Thread.Sleep(500);


                }
                //this.Dispatcher.Invoke(() => dataBox.Text = dataBox.Text += "Can not connect to device...\n"); 
                usbThreadWorking = false;
                this.Dispatcher.Invoke(() => usbbufer = "");
            }
        }


        private void traansferdata()
        {
            while (true)
            {
                if (naeedTotransfercheck)
                {
                    int a = naeedTotransfer.IndexOf("begin(");
                    int b = naeedTotransfer.IndexOf(")end");
                    naeedTotransfer = naeedTotransfer.Substring(a + 6, b - a - 6);
                    int num = 0;
                    string nacurFileme = "";
                    string curFile = "save" + num.ToString() + ".txt";
                    while (File.Exists(curFile))
                    {
                        num++;
                        curFile = "save" + num.ToString() + ".txt";
                    }
                    using (FileStream fstream = new FileStream(curFile, FileMode.OpenOrCreate))
                    {
                        byte[] array = System.Text.Encoding.Default.GetBytes(naeedTotransfer);
                        for (int i = 0; i < naeedTotransfer.Length; i++)
                        {
                            if (i % 48 == 0 && i != 0) fstream.WriteByte((byte)'\n');
                            fstream.WriteByte(array[i]);
                        }
                        this.Dispatcher.Invoke(() => dataBox.Text = dataBox.Text += "\nWrited\n");
                    }
                    naeedTotransfercheck = false;
                    naeedTotransfer = "";

                }

            }

        }

        private void usbThreadAnalys()
        {
            bool log = false;
            bool pas = false;
            while (true) { 
                while (usbThreadWorking)
                {
                    if (usbbufer.Length > 0)
                    {
                        if (usbbufer.Length > 64)
                        {
                            usbbufer = usbbufer.Substring(usbbufer.Length/3*2);
                        }
                            System.Threading.Thread.Sleep(1000);
                        //this.Dispatcher.Invoke(() => dataBox.Text = dataBox.Text += "\nRaeding\n");
                        log = false;
                        pas = false;
                        try
                        {
                            if (usbbufer.IndexOf("l") >= 0)
                            {
                                //this.Dispatcher.Invoke(() => dataBox.Text += "!" + usbbufer.Substring(usbbufer.IndexOf("l") + 3, 16) + "!");
                                if (usbbufer.IndexOf("l") >= 0 && usbbufer.IndexOf("o") >= 0 && usbbufer.IndexOf("g") >= 0)
                                {
                                    if (usbbufer[usbbufer.IndexOf("l") + 2] == 'o' && usbbufer[usbbufer.IndexOf("l") + 4] == 'g' && usbbufer[usbbufer.IndexOf("l") + 6] == ':')
                                    {

                                        this.Dispatcher.Invoke(() => { if (usbbufer.Length > 0) login = usbbufer.Substring(usbbufer.IndexOf("l") + 7); });
                                        log = true;
                                        usbbufer = "";
                                    }
                                }

                            }
                            if (usbbufer.IndexOf("p") >= 0)
                            {
                                if (usbbufer.IndexOf("p") >= 0 && usbbufer.IndexOf("a") >= 0 && usbbufer.IndexOf("s") >= 0)
                                {
                                    if (usbbufer[usbbufer.IndexOf("p") + 2] == 'a' && usbbufer[usbbufer.IndexOf("p") + 4] == 's' && usbbufer[usbbufer.IndexOf("p") + 6] == ':')
                                    {
                                        this.Dispatcher.Invoke(() => { if (usbbufer.Length > 0) password = usbbufer.Substring(usbbufer.IndexOf("p") + 7); });
                                        pas = true;
                                        usbbufer = "";
                                    }
                                }
                            }
                            if (usbbufer.IndexOf("b") >= 0)
                            {
                                System.Threading.Thread.Sleep(400);
                                if (usbbufer.IndexOf("b") >= 0 && usbbufer.IndexOf("e") >= 0 && usbbufer.IndexOf("g") >= 0 && usbbufer.IndexOf("i") >= 0 && usbbufer.IndexOf("n") >= 0 && usbbufer.IndexOf("(") >= 0)
                                {
                                    while (usbbufer.IndexOf(")") < 0 && usbbufer.IndexOf("e") < 0 && usbbufer.IndexOf("n") < 0 && usbbufer.IndexOf("d") < 0) { this.Dispatcher.Invoke(() => dataBox.Text = dataBox.Text += "."); }
                                    this.Dispatcher.Invoke(() => dataBox.Text = dataBox.Text += " Data recived...\n");
                                    naeedTotransfer = usbbufer;
                                    usbbufer = "";
                                    naeedTotransfercheck = true;
                                }

                            }
                        }
                        catch { usbbufer = ""; }
                        //System.Threading.Thread.Sleep(100);
                        if (log)
                        {
                            SendKeys.SendWait(login.Split(' ')[0]);
                            SendKeys.SendWait("{ENTER}");
                        }
                        else//System.Threading.Thread.Sleep(100);
                        if (pas)
                        {
                            byte[] bytes = Encoding.ASCII.GetBytes(password);
                            StringBuilder hex = new StringBuilder(bytes.Length * 2);
                            foreach (byte b in bytes)
                                hex.AppendFormat("{0:x2}", b);
                            password = hex.ToString();
                            SendKeys.SendWait(password);
                            SendKeys.SendWait("{ENTER}");


                        }
                        System.Threading.Thread.Sleep(100);
                    }
                }
        }

    }



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
            dataBox.ScrollToEnd();

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
            dataBox.ScrollToEnd();
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
            dataBox.ScrollToEnd();
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
            dataBox.ScrollToEnd();
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
            dataBox.ScrollToEnd();
        }
        


        private void Button_Click_7(object sender, RoutedEventArgs e)
        {
            dataBox.Text = "";
            dataBox.ScrollToEnd();
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


       
    }
}
