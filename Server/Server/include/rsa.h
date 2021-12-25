#include <stdio.h>
#include <bitset>
#include <vector>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/miller_rabin.hpp>
#include <iostream>
#include <iomanip>
#include <boost/multiprecision/miller_rabin.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/integer/common_factor.hpp>
#include <algorithm>
#include <boost/integer/mod_inverse.hpp>
#include <bitset>
#include <string>

class Rsa
{
    boost::multiprecision::cpp_int p,q,e,n,d,euler,random;
    static constexpr int size_1024 = 1024;
    static constexpr int size_512 = 512;
    static constexpr int size_256 = 256;
    boost::multiprecision::cpp_int generate_prime(int bit_length);
    static boost::multiprecision::cpp_int mod_pow(boost::multiprecision::cpp_int base,
    boost::multiprecision::cpp_int exponent,
    boost::multiprecision::cpp_int mod);
    static bool check_overflow(boost::multiprecision::cpp_int num1, boost::multiprecision::cpp_int num2);
    
    public:
    std::string ascii_number_to_text(std::string s);
    std::string text_to_ascii_number(std::string s);
    Rsa(int bit_length);
    Rsa();
    Rsa(boost::multiprecision::cpp_int e, boost::multiprecision::cpp_int d, boost::multiprecision::cpp_int n);
    std::string decrypt(std::string input);
    std::string encrypt(std::string plaintext);
    static std::string encrypt(std::string plaintext, boost::multiprecision::cpp_int e, boost::multiprecision::cpp_int n);
    static std::string decrypt(std::string input, boost::multiprecision::cpp_int d, boost::multiprecision::cpp_int n);
};