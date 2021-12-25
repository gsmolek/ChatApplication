using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Numerics;
using System.Security.Cryptography;

namespace WindowsApplication
{
    class RSA
    {
        private readonly int bitLength = 1024;
        private BigInteger p, q, n;
        private BigInteger e;//Encryption public key
        private BigInteger d;//decryption private key

        public BigInteger P { get => p; }
        public BigInteger Q { get => q; }
        public BigInteger N { get => n; }
        public BigInteger E { get => e; }
        public BigInteger D { get => d; }

        public RSA()
        {
            this.initializePQED();
        }
        public RSA(int length)
        {
            this.initializePQED(length);
        }
        public RSA(BigInteger e, BigInteger d, BigInteger n)
        {
            this.e = e;
            this.n = n;
            this.d = d;
        }
        public RSA(BigInteger p, BigInteger q, BigInteger n, BigInteger e, BigInteger d)
        {
            this.q = q;
            this.p = p;
            this.e = e;
            this.n = n;
            this.d = d;
        }
        //public byte[] encryption(byte[] bytes)
        public string encryption(string str)
        {
            BigInteger cipher = BigInteger.Parse(str);
             cipher = BigInteger.ModPow(cipher, e, n);
            return cipher.ToString();
        }
        public string textToAsciiNumber(string str)
        {
            StringBuilder output = new StringBuilder();
            foreach(char c in str)
            {
                if (Char.IsLetter(c) || Char.IsDigit(c))
                {
                    output.Append((int)c);   
                }
            }
            return output.ToString();
        }
        public string AsciiNumberToText(string str)
        {
            StringBuilder output = new StringBuilder();
            int number = 0;
            for(int i = 0; i < str.Length; i++)
            {
                number = number * 10 + (str[i]-'0');
                if (Char.IsLetter((char)number) || Char.IsDigit((char)number))
                {
                    char c = (char)number;
                    output.Append(c);
                    number = 0;
                }
            }
            return output.ToString();
        }
        public string decryption(string str)
        {
            BigInteger plaintext = BigInteger.Parse(str);
            plaintext = BigInteger.ModPow(plaintext, d, n);
            return plaintext.ToString();
        }
        public static string encryption(string str, BigInteger e, BigInteger n)
        {
            BigInteger cipher = BigInteger.Parse(str);
            cipher = BigInteger.ModPow(cipher, e, n);
            return cipher.ToString();

        }
        public static string decryption(string str, BigInteger d, BigInteger n)
        {
            BigInteger plaintext = BigInteger.Parse(str);
            plaintext = BigInteger.ModPow(plaintext, d, n);
            return plaintext.ToString();
        }

        private void initializePQED()
        {
            var csp = new RSACryptoServiceProvider(bitLength);
            var param = csp.ExportParameters(true);
            p = new BigInteger(param.P.Reverse().Concat(new byte[1]).ToArray());
            q = new BigInteger(param.Q.Reverse().Concat(new byte[1]).ToArray());
            e = new BigInteger(param.Exponent.Reverse().Concat(new byte[1]).ToArray());
            d = new BigInteger(param.D.Reverse().Concat(new byte[1]).ToArray());
            n = new BigInteger(param.Modulus.Reverse().Concat(new byte[1]).ToArray());
        }
        private void initializePQED(int length)
        {
            var csp = new RSACryptoServiceProvider(length);
            var param = csp.ExportParameters(true);
            p = new BigInteger(param.P.Reverse().Concat(new byte[1]).ToArray());
            q = new BigInteger(param.Q.Reverse().Concat(new byte[1]).ToArray());
            e = new BigInteger(param.Exponent.Reverse().Concat(new byte[1]).ToArray());
            d = new BigInteger(param.D.Reverse().Concat(new byte[1]).ToArray());
            n = new BigInteger(param.Modulus.Reverse().Concat(new byte[1]).ToArray());
        }
    }
}
