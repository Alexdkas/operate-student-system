#pragma once

#include "User.h"

#include <string>

class AdminUser : public User
{
private:
    int RecordID;

public:
    AdminUser(int id, const std::string &username, const std::string &hashedPassword, int recordID)
        : User(id, username, hashedPassword, UserType::Admin), RecordID(recordID) {}

    void displaymenu() const override;
    void addUser(const std::string &username, const std::string &hashedPassword, UserType userType); // Function to add a new user
    void removeUser(int userId);                                                                     // Function to remove a user by their ID
    void viewAllUsers() const;                                                                       // Function to view all users in the system
    void GetUserDetails(int userId) const;                                                           // Function to get details of a specific user by their ID
    void viewSystemLogs() const;                                                                     // Function to view system logs for administrative purposes
};