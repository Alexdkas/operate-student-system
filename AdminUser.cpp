#include "AdminUser.h"

#include <iostream>

void AdminUser::displaymenu() const
{
    std::cout << "=== Admin Menu ===\n";
    std::cout << "1. Add user\n";
    std::cout << "2. Remove user\n";
    std::cout << "3. View all users\n";
    std::cout << "4. View user details\n";
    std::cout << "5. View system logs\n";
}

void AdminUser::addUser(const std::string &username, const std::string &hashedPassword, UserType userType)
{
    std::cout << "Admin adds user: " << username << " (type: " << static_cast<int>(userType) << ")\n";
}

void AdminUser::removeUser(int userId)
{
    std::cout << "Admin removes user with ID: " << userId << '\n';
}

void AdminUser::viewAllUsers() const
{
    std::cout << "Viewing all users in the system.\n";
}

void AdminUser::GetUserDetails(int userId) const
{
    std::cout << "Getting details for user ID: " << userId << '\n';
}

void AdminUser::viewSystemLogs() const
{
    std::cout << "Viewing system logs.\n";
}
