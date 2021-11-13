using System;
using System.IO;
using System.Security.Cryptography;

using System.Collections.Generic;
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
using Windows;
using System.Numerics;

namespace WindowsApplication
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private Windows.Client client;

        public Client Client { get => client; set => client = value; }

        public MainWindow()
        {
            RSA rsa;
            string workingDirectory = Environment.CurrentDirectory;
            string keysFilePath = Directory.GetParent(workingDirectory).Parent.FullName+@"\Files\cryptography\keys.txt";
            if (File.Exists(keysFilePath))
            {
                
                string[] lines = File.ReadAllLines(keysFilePath);
                BigInteger[] rsaInfo = new BigInteger[5];
                for (int i = 0; i < 5; i++)
                {
                    rsaInfo[i] = BigInteger.Parse(lines[i], System.Globalization.NumberStyles.Any);
                }
                rsa = new RSA(rsaInfo[0], rsaInfo[1], rsaInfo[2], rsaInfo[3], rsaInfo[4]);
            }
            else 
            {
                rsa = new RSA();
                FileStream fileStream = File.Create(keysFilePath);
                fileStream.Close();
                string[] lines =
                    {
                    rsa.P.ToString(),
                    rsa.Q.ToString(),
                    rsa.N.ToString(),
                    rsa.E.ToString(),
                    rsa.D.ToString()
                };
                File.WriteAllLines(keysFilePath, lines);
            }
            client = new Windows.Client("127.0.0.1", 5555);
            
            Console.WriteLine("P: " + rsa.P);
            Console.WriteLine("Q: " + rsa.Q);
            byte[] str = Encoding.ASCII.GetBytes("hello");
            byte[] res = rsa.encryption(str);
            Console.WriteLine("encrypted: "+Encoding.UTF8.GetString(res, 0, res.Length));
            string res_str = Encoding.UTF8.GetString(res, 0, res.Length);
            client.Send(res_str);
            byte[] dec = rsa.decryption(res);
            Console.WriteLine("decrypted: " + Encoding.UTF8.GetString(dec, 0, dec.Length));
            string res1= Cryptology.hash("hello world!");
            Console.WriteLine("hash: " + res1);
            InitializeComponent();


        }

        private void TextBox_TextChanged(object sender, TextChangedEventArgs e)
        {

        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            Manager manager = new Manager();
            this.Hide();
            manager.Show();
        }

        private void Window_Activated(object sender, EventArgs e)
        {
            if (client.Connected)
                connectionText.Visibility = Visibility.Hidden;
            else
                connectionText.Text = "Unable to reach the server";
        }


        private void connectionText_Loaded(object sender, RoutedEventArgs e)
        {

        }

        private void connectionText_ContextMenuOpening(object sender, ContextMenuEventArgs e)
        {

        }

        private void connectionText_Initialized(object sender, EventArgs e)
        {

        }
    }
}
