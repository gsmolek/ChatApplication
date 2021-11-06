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

        public Client(string ip, int port)
        {
            ipAddress = IPAddress.Parse(ip);

            clientSocket = new TcpClient();
            clientSocket.Connect(ipAddress, port);
            networkStream = clientSocket.GetStream();
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
    }
}
