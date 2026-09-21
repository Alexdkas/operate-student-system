#pragma once

#include <string>

class CryptoEngine
{
public:
    CryptoEngine();
    ~CryptoEngine();

    static std::string encrypt(const std::string &plaintext);                                   // Function to encrypt a plaintext string
    static std::string decrypt(const std::string &ciphertext);                                  // Function to decrypt a ciphertext string
    static std::string hashPassword(const std::string &password);                               // Function to hash a password using a secure hashing algorithm
    static bool verifyPassword(const std::string &password, const std::string &hashedPassword); // Function to verify if a password matches the hashed password
};