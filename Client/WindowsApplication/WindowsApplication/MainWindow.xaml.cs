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
        private BigInteger serverE = BigInteger.Parse("438814270853093994085182747074266407295061167680798662233005953928739227816300271445412071924669188444568349316823207638498671216467817937805801770837289");
        private BigInteger ServerN = BigInteger.Parse("20526766413795073776754021273959414186564998880159985618870658181689441888484130763277389830428692528202488992850869808640159588725297406273481320336942630855144500627473825226625951519157939019067104740005250022497092815361703109519347397643958970872943285476778018240125393132105054692669578962863440894603836489597198326894764981211539494593024618464042234006822899281519309445068742950046664237747630826665724665379406896640927819922688745585693716772517155708251843681268099717010790743892359116080401707809828186428628374576398698878603151231260696914863207145913365327930099137255910263733972825828496007533747");
        
        private BigInteger signatureE = BigInteger.Parse("92371000115221489172430898249443196180751244427929364157379963645415911179197");
        private BigInteger signatureN = BigInteger.Parse("8341897561232117566949145541662621758846531923064799980145763045398065438644001216276180923601144277711752630554943203720057498305163142794015535827490076696549458598753135440745586487177635964337244661264276744913993360980905577916048866580909092671463779229261987126962684128998276991428334739623358324001");
        private BigInteger signatureD = BigInteger.Parse("7246727715135478344434965204632528190247914935912726903459150694394781241435146299402250068269456794746168634028824669218312436920254509222964041205721355888142056334838664303126197853086182631113217057472804600661802536165402876694143671530102704707990072290554877780804817828718604810833278571025533251733");

        private BigInteger serverSignatureE = BigInteger.Parse("35259884238401222418361536194277052540060258369911178249856361363735145530691");
        private BigInteger serverSignatureN = BigInteger.Parse("6970594987649283492041515142966617748429401310104401989997931161968805865725976038066926903538743918045724821813674951119683428059289789545072656444103092139279692219155527103269769248476207662065501104402062332975499533423207161563681687611145714232739547888696801359948254017237046854034738890056957555673");

        private RSA rsa;
        public Client Client { get => client; set => client = value; }

        public MainWindow()
        {
            
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
            client = new Windows.Client("172.22.144.1", 5555);
            /*
            Console.WriteLine("P: " + rsa.P);
            Console.WriteLine("Q: " + rsa.Q);
            string ats = rsa.textToAsciiNumber("hello");
            string sta = rsa.AsciiNumberToText(ats);
            Console.WriteLine(ats);
            Console.WriteLine(sta);
            string res = rsa.encryption(ats);
            Console.WriteLine("encrypted: "+res);
            
            string dec = rsa.decryption(res);
            Console.WriteLine("decrypted: " + dec);
            string res1= Cryptology.hash("hello world!");
            Console.WriteLine("hash: " + res1);
            InitializeComponent();
            */
        }

        private void TextBox_TextChanged(object sender, TextChangedEventArgs e)
        {

        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            if ( !username_input.Text.Equals("") && !password_input.Equals(""))
            {
                string request = "000";
                string usernamePad = "000";
                string passwordPad = "000";
                string username = username_input.Text;
                string password = Cryptology.hash(password_input.Password);
                usernamePad += username.Length;
                passwordPad += password.Length;
                request += usernamePad[usernamePad.Length - 3];
                request += usernamePad[usernamePad.Length - 2];
                request += usernamePad[usernamePad.Length - 1];
                request += passwordPad[passwordPad.Length - 3];
                request += passwordPad[passwordPad.Length - 2];
                request += passwordPad[passwordPad.Length - 1];
                request += username;
                request += password.ToLower();
                request = rsa.textToAsciiNumber(request);
                Console.WriteLine(request); 
                request = RSA.encryption(request,serverE, ServerN);
                Console.WriteLine("hash: ");
                Console.WriteLine(password);
                client.Send(request);
                request = client.recieve();
                Console.WriteLine(request);
                if (request == "ok")
                {
                    Manager manager = new Manager(username);
                    this.Hide();
                    manager.Show();
                }
            }
            
            
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
