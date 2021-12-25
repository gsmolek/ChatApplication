using System;
using System.Collections.Generic;
using System.Linq;
using System.Numerics;
using System.Text;
using System.Threading.Tasks;

namespace WindowsApplication
{
    internal class DigitalSignature
    {
        private RSA rsa = new RSA();
        private BigInteger N;
        private BigInteger D;
        private BigInteger E;
        public DigitalSignature()
        {
            rsa = new RSA(512);
            this.N = rsa.N;
            this.E = rsa.E;
            this.D = rsa.D;
        }
        public DigitalSignature(BigInteger n, BigInteger e, BigInteger d)
        {
            rsa = new RSA(512);
            this.N = n;
            this.E = e;
            this.D = d;
        }
        public string digitalSigning(string message, string code)
        {
            string output = "";
            string message_length = "000";
            string hash_length = "000";
            string hash;
            output += code;
            message_length += message.Length;
            output += message_length[message_length.Length - 3];
            output += message_length[message_length.Length - 2];
            output += message_length[message_length.Length - 1];
            output += message;
            hash = Cryptology.hash(message);
            hash = rsa.textToAsciiNumber(hash);
            hash = rsa.decryption(hash);
            output += rsa.textToAsciiNumber(output);
            output += hash;
            hash_length += hash.Length;
            output += hash_length[hash.Length - 3];
            output += hash_length[hash.Length - 2];
            output += hash_length[hash.Length - 1];
            return output;

        }
        public string checkingDigitalSignature(string message)
        {
            Friend friend;
            string temp_message = rsa.AsciiNumberToText(message);
            string username, message_received, hash;
            int type, tCode, userCode, hashLength;
            type = int.Parse(temp_message.Substring(0, 3));
            tCode = int.Parse(temp_message.Substring(3, 3));
            userCode = int.Parse((temp_message.Substring(6, 3)));
            hashLength = int.Parse(((temp_message.Substring(message.Length - 3, 3))));
            username = temp_message.Substring(9, userCode);
            message_received = temp_message.Substring(0, tCode + userCode - 1);
            hash = message.Substring(message.Length - hashLength - 3, hashLength);
            friend = Friend.get_username(username);
            hash = RSA.encryption(hash, friend.SignatureE, friend.SignatureN);
            hash = rsa.AsciiNumberToText(hash);
            string hashNew = Cryptology.hash(message_received.Substring(6, message_received.Length - 6));
            if (hash.CompareTo(hashNew) == 0)
            {
                return message_received;
            }
            return "failed";
        }
    }
}
