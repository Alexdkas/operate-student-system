#include "CryptoEngine.h"

#include <cstdint>
#include <iomanip>
#include <sstream>

namespace
{
std::string toHex(std::uint64_t value)
{
    std::ostringstream stream;
    stream << std::hex << std::setw(16) << std::setfill('0') << value;
    return stream.str();
}
}

CryptoEngine::CryptoEngine() = default;
CryptoEngine::~CryptoEngine() = default;

std::string CryptoEngine::encrypt(const std::string& plaintext)
{
    std::string result = plaintext;
    const std::string key = "student-system";

    for (std::size_t i = 0; i < result.size(); ++i)
    {
        result[i] = static_cast<char>(result[i] ^ key[i % key.size()]);
    }
    return result;
}

std::string CryptoEngine::decrypt(const std::string& ciphertext)
{
    return encrypt(ciphertext);
}

std::string CryptoEngine::hashPassword(const std::string& password)
{
    std::uint64_t hash = 14695981039346656037ull;

    for (unsigned char ch : password)
    {
        hash ^= static_cast<std::uint64_t>(ch);
        hash *= 1099511628211ull;
    }

    return "fnv1a_" + toHex(hash);
}

bool CryptoEngine::verifyPassword(const std::string& password, const std::string& hashedPassword)
{
    return hashPassword(password) == hashedPassword;
}


