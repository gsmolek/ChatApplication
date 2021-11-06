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
        public byte[] encryption(byte[] bytes)
        {
            BigInteger cipher = new BigInteger(bytes);
             cipher = BigInteger.ModPow(cipher, e, n);
            return cipher.ToByteArray();
        }
        public byte[] decryption(byte[] bytes)
        {
            BigInteger plaintext = new BigInteger(bytes);
            plaintext = BigInteger.ModPow(plaintext, d, n);
            return plaintext.ToByteArray();
        }
        public static byte[] encryption(byte[] bytes, BigInteger e, BigInteger n)
        {
            BigInteger cipher = new BigInteger(bytes);
            cipher = BigInteger.ModPow(cipher, e, n);
            return cipher.ToByteArray();

        }
        public static byte[] decryption(byte[] bytes, BigInteger d, BigInteger n)
        {
            BigInteger plaintext = new BigInteger(bytes);
            plaintext = BigInteger.ModPow(plaintext, d, n);
            return plaintext.ToByteArray();
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
    }
}
