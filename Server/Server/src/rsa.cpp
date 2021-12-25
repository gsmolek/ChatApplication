#include "rsa.h"

Rsa::Rsa(int bit_length)
{
    p = generate_prime(bit_length);
    q = generate_prime(bit_length);
    n = p * q ;
    euler = (p - 1) * (q - 1);
    e = generate_prime(bit_length/2);
    while ((boost::integer::gcd( euler, e ) > 1 ) && ( e < euler ))
    {
        e+=1;
    }
    d = boost::integer::mod_inverse( e, euler );
    std::cout << "n: " << n << std::endl;
    std::cout << "e: " << e << std::endl;
    std::cout << "d: " << d << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
}
Rsa::Rsa()
{
    n = boost::multiprecision::cpp_int{"20526766413795073776754021273959414186564998880159985618870658181689441888484130763277389830428692528202488992850869808640159588725297406273481320336942630855144500627473825226625951519157939019067104740005250022497092815361703109519347397643958970872943285476778018240125393132105054692669578962863440894603836489597198326894764981211539494593024618464042234006822899281519309445068742950046664237747630826665724665379406896640927819922688745585693716772517155708251843681268099717010790743892359116080401707809828186428628374576398698878603151231260696914863207145913365327930099137255910263733972825828496007533747"};
    e = boost::multiprecision::cpp_int{"438814270853093994085182747074266407295061167680798662233005953928739227816300271445412071924669188444568349316823207638498671216467817937805801770837289" };
    d = boost::multiprecision::cpp_int{"14954664479091906365074472130063554121547518494341392395511209707012820009533261683466978409071967471085426790421536767975922796291579108943189365070658163839547966694033582815644656973971705401606834443201853767905106070482541528199748749557855315976369425623143163706245611118620252137211560661201486905500342808585588524183602455930329276003961639525979755579680340352047622146135822208052917160582546172404712292197442600475041907002286977201775276311475597187357439459858596710872079746696675167071015005344390343209657494967605762303426407507296596290580324547073568725580269693480176791345488839030127224171417" };

}
bool Rsa::check_overflow(boost::multiprecision::cpp_int num1, boost::multiprecision::cpp_int num2)
{
    boost::multiprecision::cpp_int value = num1 * num2;
    return (value < num1);
}
std::string Rsa::ascii_number_to_text(std::string s)
{
    std::string output = "";
    int number = 0;
    for (int i = 0; i < s.size(); ++i)
    {
        number = number * 10 + (s.at(i) - '0');
        if ((number >= 32 && number <= 122))
        {
            char ch = (char)number;
            output += static_cast<char>(ch);
            number = 0;
        }
    }
    return output;
}
std::string Rsa::text_to_ascii_number(std::string s)
{
    std::stringstream ss;
    std::vector<std::byte> bytes;
    std::string output = "";
    for (char s_char : s)
    {
        std::bitset<8> bits(s_char);
        bytes.push_back(std::byte(s_char));
        ss << int(s_char);
    }
    output = ss.str();
    return output;
}
boost::multiprecision::cpp_int Rsa::mod_pow(boost::multiprecision::cpp_int base,
    boost::multiprecision::cpp_int exponent,
    boost::multiprecision::cpp_int mod)
    {
        if( mod == 1 )
        {
            return 0;
        }
        if(!check_overflow(mod-1,mod-1))
        {
            boost::multiprecision::cpp_int result = 1;
            base = base % mod;
            while( exponent > 0)
            {
                if( exponent % 2 == 1)
                {
                    result = (result * base) % mod;
                }
                exponent = exponent >> 1;
                base = (base * base) % mod ;
            }
            return result; 
        }
        return -11111;

    }
Rsa::Rsa(boost::multiprecision::cpp_int e, boost::multiprecision::cpp_int d, boost::multiprecision::cpp_int n)
{
        this->d=d;
        this->e=e;
        this->n=n;
}
std::string Rsa::encrypt(std::string plaintext)
{
    std::string str = "";
    boost::multiprecision::cpp_int output(plaintext);
    std::stringstream stream;
    output = mod_pow(output,e,n);
    stream << output;
    stream >> str;
    return str;
}
std::string Rsa::encrypt(std::string plaintext, boost::multiprecision::cpp_int e, boost::multiprecision::cpp_int n)
{
    std::string str = "";
    boost::multiprecision::cpp_int output(plaintext);
    std::stringstream stream;
    output = mod_pow(output, e, n);
    stream << output;
    stream >> str;
    return str;
}
std::string Rsa::decrypt(std::string input, boost::multiprecision::cpp_int d, boost::multiprecision::cpp_int n)
{
    std::string str = "";
    boost::multiprecision::cpp_int output(input);
    std::stringstream stream;
    output = mod_pow(output, d, n);
    stream << output;
    stream >> str;
    return str;
}
std::string Rsa::decrypt(std::string cyphertext)
{
    std::string str = "";
    boost::multiprecision::cpp_int output(cyphertext);
    std::stringstream stream;
    output = mod_pow(output,d,n);
    stream << output;
    stream >> str;
    return str;
}
boost::multiprecision::cpp_int Rsa::generate_prime(int bit_length)
{
    typedef boost::multiprecision::cpp_int int_type;
    boost::random::mt11213b base_gen(clock());
    boost::random::independent_bits_engine<boost::random::mt11213b, size_1024, int_type> gen1024(base_gen);
    boost::random::independent_bits_engine<boost::random::mt11213b, size_512, int_type> gen512(base_gen);
    boost::random::independent_bits_engine<boost::random::mt11213b, size_256, int_type> gen256(base_gen);
    
    boost::random::mt19937 gen2(clock());
    for(unsigned i = 0; i < 100000; ++i)
    {
      int_type num;
      if(bit_length == size_1024)
      {
          num = gen1024();
      }
      else if(bit_length == size_512)
      {
          num = gen512();
      }
      else if (bit_length == size_256)
      {
          num = gen256();
      }
      if(miller_rabin_test(num, 25, gen2))
      {
        return num;
      }
    }
    return 0;
}

/*
int main()
{
    Rsa t(1024);
    std::string text = t.encrypt("123456789");
    std::cout<< text << std::endl;
    std::cout<< t.decrypt(text) << std::endl;
    return 0;
}
*/