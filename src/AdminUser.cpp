#include "AdminUser.h"
#include "FileMandger.h"
#include "Logger.h"
#include "StudentUser.h"
#include "TeacherUser.h"

namespace
{
    std::string userTypeToString(UserType type)
    {
        switch (type)
        {
        case UserType::Student:
            return "Student";
        case UserType::Teacher:
            return "Teacher";
        case UserType::Admin:
            return "Admin";
        default:
            return "Unknown";
        }
    }

    bool userExists(const std::string &username)
    {
        const auto users = FileManager::getInstance().loadUsers();
        for (const auto &user : users)
        {
            if (user && user->getUsername() == username)
            {
                return true;
            }
        }
        return false;
    }

    int nextUserId()
    {
        const auto users = FileManager::getInstance().loadUsers();
        int maxId = 0;

        for (const auto &user : users)
        {
            if (user && user->getId() > maxId)
            {
                maxId = user->getId();
            }
        }

        return maxId + 1;
    }
}

void AdminUser::displaymenu() const
{
    Logger::log("=== Admin Menu ===");
    Logger::log("1. Add user");
    Logger::log("2. Remove user");
    Logger::log("3. View all users");
    Logger::log("4. View user details");
    Logger::log("5. View system logs");
}

void AdminUser::addUser(const User &user)
{
    addUser(user.getUsername(), user.getHashedPassword(), user.getUserType());
}

void AdminUser::addUser(const std::string &username, const std::string &hashedPassword, UserType userType)
{
    if (username.empty())
    {
        Logger::log("Username cannot be empty.");
        return;
    }

    if (userExists(username))
    {
        Logger::log("User already exists: " + username);
        return;
    }

    Logger::log("Admin adds user: " + username + " (type: " + userTypeToString(userType) + ")");

    std::shared_ptr<User> newUser;
    const int userId = nextUserId();
    const int recordId = userId;

    switch (userType)
    {
    case UserType::Student:
        newUser = std::make_shared<StudentUser>(userId, username, hashedPassword, recordId);
        break;
    case UserType::Teacher:
        newUser = std::make_shared<TeacherUser>(userId, username, hashedPassword, recordId);
        break;
    case UserType::Admin:
        newUser = std::make_shared<AdminUser>(userId, username, hashedPassword, recordId);
        break;
    default:
        Logger::log("Unknown user type requested.");
        return;
    }

    if (newUser)
    {
        FileManager::getInstance().addUser(newUser);
    }
}

void AdminUser::removeUser(int userId)
{
    Logger::log("Admin removes user with ID: " + std::to_string(userId));
    FileManager::getInstance().deleteUser(userId);
}

void AdminUser::viewAllUsers() const
{
    Logger::log("Viewing all users in the system.");
    const auto users = FileManager::getInstance().loadUsers();
    for (const auto &user : users)
    {
        if (user)
        {
            Logger::log("User ID: " + std::to_string(user->getId()) + ", Username: " + user->getUsername() + ", Type: " + userTypeToString(user->getUserType()));
        }
    }
}

void AdminUser::GetUserDetails(int userId) const
{
    Logger::log("Getting details for user ID: " + std::to_string(userId));
    const auto users = FileManager::getInstance().loadUsers();
    for (const auto &user : users)
    {
        if (user && user->getId() == userId)
        {
            Logger::log("User ID: " + std::to_string(user->getId()) + ", Username: " + user->getUsername() + ", Type: " + userTypeToString(user->getUserType()));
            return;
        }
    }
    Logger::log("User not found.");
}

void AdminUser::viewSystemLogs() const
{
    Logger::log("Viewing system logs.");
}
