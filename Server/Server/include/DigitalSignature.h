#include<iostream>
#include<string>
#include<functional>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/function.hpp>
#include <boost/function_equal.hpp>
/*
* DIGITAL SIGNATURE
* 1) Alice creates a one way hash of the file.
* 2) Alice encrypts the hash with her private key = Alice signing the document.
* 3) Alice sends the file with the encrypted hash to Bob.
* 4) Bob also creates a hash of the file recieved from Alice.
* 5) Using Alice's private key Bob decrypts the hash signed by Alice.
* 6) If the signed hash matches the hash value he created the signature is valid.
*/
class DigitalSignature
{
public:

    static std::string signing(boost::function<std::string(const std::string&, boost::multiprecision::cpp_int&,
        boost::multiprecision::cpp_int&)> signing_function,
        std::function<std::string(const std::string&)> hash, 
        boost::multiprecision::cpp_int n,boost::multiprecision::cpp_int d,
        std::string& input);

    static bool validate(boost::function<std::string(const std::string& hash,
        boost::multiprecision::cpp_int&,
        boost::multiprecision::cpp_int&)> signing_function,
        boost::multiprecision::cpp_int n, boost::multiprecision::cpp_int e,
        std::function<std::string(const std::string&)> hash,
        const std::string& message_recieved,
        const std::string& hash_recieved);


};
