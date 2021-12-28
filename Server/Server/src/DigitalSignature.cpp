#include "DigitalSignature.h" 

std::string DigitalSignature::signing(boost::function<std::string(const std::string&, boost::multiprecision::cpp_int&,
    boost::multiprecision::cpp_int&)> signing_function,
    std::function<std::string(const std::string&)> hash,
    boost::multiprecision::cpp_int n,boost::multiprecision::cpp_int d,
    std::string& input)
{
    std::string hash_ref{ hash(input) };
    std::string& signing_ref = signing_function(hash_ref, d, n);
    return input.append(signing_ref);
}
bool DigitalSignature::validate(boost::function<std::string(const std::string& hash, boost::multiprecision::cpp_int&,
    boost::multiprecision::cpp_int&)> signing_function, boost::multiprecision::cpp_int n, boost::multiprecision::cpp_int e,
    std::function<std::string(const std::string&)> hash,
    const std::string& message_recieved, const std::string& hash_recieved)
{
    std::string hash_value_ref{ signing_function(hash_recieved,e,n) };
    std::string&& hash_ref{ hash(message_recieved) };
    if (hash_ref == hash_value_ref)
    {
        return true;
    }
    return false;
}