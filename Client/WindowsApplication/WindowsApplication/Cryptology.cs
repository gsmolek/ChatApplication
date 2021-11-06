using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Security.Cryptography;
using System.Numerics;

namespace WindowsApplication
{
    class Cryptology
    {
        private readonly int bitLength = 1024;
        private BigInteger p, q, n, euler, one = BigInteger.One;
        private BigInteger e;//Encryption key
        private BigInteger d;//decryption key

        public static string hash(string plaintext)
        {
            SHA256.Create();
            byte[] sourceByte = Encoding.UTF8.GetBytes(plaintext);
            byte[] hashByte = SHA256.Create().ComputeHash(sourceByte);
            string output = BitConverter.ToString(hashByte).Replace("-", string.Empty);
            return output;
        }
    }
}
