using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Numerics;
using System.Text;
using System.Threading.Tasks;
using System.Collections;

namespace WindowsApplication
{
    internal class Friend
    {
        private string username;
        private string nickname;
        private static List<Friend> friends = new List<Friend>();
        private BigInteger signatureN;
        private BigInteger signatureE;
        private BigInteger publicN;
        private BigInteger publicE;

        public string Username { get => username; set => username = value; }
        public string Nickname { get => nickname; set => nickname = value; }
        public BigInteger SignatureN { get => signatureN; set => signatureN = value; }
        public BigInteger SignatureE { get => signatureE; set => signatureE = value; }
        public BigInteger PublicN { get => publicN; set => publicN = value; }
        public BigInteger PublicE { get => publicE; set => publicE = value; }
        internal static List<Friend> Friends { get => friends; set => friends = value; }

        public static Friend get_username(string username)
        {
            for (int i = 0; i < friends.Count; i++)
            {
                if (friends[i].Username == username)
                {
                    return friends[i];
                }
            }
            return null;
        }
        public static void load(string username)
        {
            string directory = @"\Files\friends\friends"+username+".txt";
            string workingDirectory = Environment.CurrentDirectory;
            string keysFilePath = Directory.GetParent(workingDirectory).Parent.FullName + directory;
            
            if (File.Exists(keysFilePath))
            {
                string[] lines = File.ReadAllLines(keysFilePath);
                string[] info = new string[lines.Length];
                for (int i = 0; i < info.Length; i+=6)
                {
                    Friend f = new Friend();
                    f.username = lines[i];
                    f.nickname = lines[i+1];
                    f.signatureN = BigInteger.Parse(lines[i + 2]);
                    f.signatureE = BigInteger.Parse(lines[i + 3]);
                    f.publicN = BigInteger.Parse(lines[i + 4]);
                    f.publicE = BigInteger.Parse(lines[i + 5]);
                    Friends.Add(f);
                }
            }
            else
            {            
                FileStream fileStream = File.Create(keysFilePath);
                fileStream.Close();
            }
        }
        public static void addFriend(Friend friend,string username)
        {
            string directory = @"\Files\friends\friends" + username + ".txt";
            string workingDirectory = Environment.CurrentDirectory;
            string keysFilePath = Directory.GetParent(workingDirectory).Parent.FullName + directory;

            if (File.Exists(keysFilePath))
            {
                string[] lines = File.ReadAllLines(keysFilePath);
                string[] info = new string[lines.Length];
                string user = friend.username;
                bool flag = false;
                for (int i = 0; i < lines.Length; i += 6)
                {
                    if (lines[i] == user)
                    {
                        flag = true;
                    }
                }
                if (!flag)
                {
                    lines = new string[6];
                    lines[0] = friend.username;
                    lines[1] = friend.nickname;
                    lines[2] = friend.signatureN.ToString();
                    lines[3] = friend.signatureE.ToString();
                    lines[4] = friend.publicN.ToString();
                    lines[5] = friend.publicE.ToString();
                    File.AppendAllLines(keysFilePath, lines);
                    Friends.Add(friend);
                }
            }
            else
            {
                FileStream fileStream = File.Create(keysFilePath);
                fileStream.Close();
                string[] lines = new string[6];
                lines[0] = friend.username;
                lines[1] = friend.nickname;
                lines[2] = friend.signatureN.ToString();
                lines[3] = friend.signatureE.ToString();
                lines[4] = friend.publicN.ToString();
                lines[5] = friend.publicE.ToString();
                File.WriteAllLines(keysFilePath, lines);
                Friends.Add(friend);
            }
        }
    }

}
