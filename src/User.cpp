#include "User.h"
#include "CryptoEngine.h"

bool User::checkPassword(const std::string &password) const
{
    return CryptoEngine::verifyPassword(password, getHashedPassword());
}
