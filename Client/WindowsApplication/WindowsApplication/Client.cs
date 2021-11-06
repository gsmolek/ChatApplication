using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Net;
using System.Net.Sockets;

namespace Windows
{
    public class Client
    {
        private System.Net.Sockets.TcpClient clientSocket;
        private System.Net.IPAddress ipAddress;
        private NetworkStream networkStream;
        private bool connected = false;

        public bool Connected { get => connected; set => connected = value; }

        public Client(string ip, int port)
        {
            ipAddress = IPAddress.Parse(ip);
            clientSocket = new TcpClient();
            try
            {
                clientSocket.Connect(ipAddress, port);
                networkStream = clientSocket.GetStream();
                connected = true;
            }
            catch (SocketException socketExecption)
            {
                connected = false;
            }
        }

        public void Send(string message)
        {
                byte[] tempByteArray = Encoding.ASCII.GetBytes(message);
                networkStream.Write(tempByteArray, 0, tempByteArray.Length);   
        }
        public string recieve()
        {
            string message = string.Empty;
            byte[] tempByteArray = new byte[256];
            int bytes = networkStream.Read(tempByteArray, 0, tempByteArray.Length);
            message = System.Text.Encoding.ASCII.GetString(tempByteArray, 0, tempByteArray.Length);
            return message;
        }
        ~Client()
        {
            networkStream.Close();
            clientSocket.Close();
        }
        public NetworkStream GetNetworkStream()
        {
            return networkStream;
        }
        public TcpClient GetTcpClient()
        {
            return clientSocket;
        }
    }
}
