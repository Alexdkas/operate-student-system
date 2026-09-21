#include <iostream>
#include <limits>
#include <memory>
#include <sstream>
#include <string>

#include "AdminUser.h"
#include "CryptoEngine.h"
#include "FileMandger.h"
#include "StudentUser.h"
#include "TeacherUser.h"

namespace
{
    void ensureDefaultAdmin()
    {
        const auto users = FileManager::getInstance().loadUsers();
        for (const auto &user : users)
        {
            if (user && user->getUsername() == "admin")
            {
                return;
            }
        }

        int nextId = 1;
        for (const auto &user : users)
        {
            if (user && user->getId() >= nextId)
            {
                nextId = user->getId() + 1;
            }
        }

        const auto admin = std::make_shared<AdminUser>(nextId, "admin", CryptoEngine::hashPassword("admin123"), nextId);
        FileManager::getInstance().addUser(admin);
        std::cout << "Default admin created: username=admin, password=admin123\n";
    }

    std::string readString(const std::string &prompt)
    {
        std::string value;
        std::cout << prompt;
        std::getline(std::cin, value);
        return value;
    }

    int readInt(const std::string &prompt)
    {
        std::string input = readString(prompt);
        int value = 0;
        std::stringstream stream(input);
        stream >> value;
        return value;
    }

    double readDouble(const std::string &prompt)
    {
        std::string input = readString(prompt);
        double value = 0.0;
        std::stringstream stream(input);
        stream >> value;
        return value;
    }

    UserType readRoleChoice()
    {
        while (true)
        {
            std::cout << "Select role:\n";
            std::cout << "1. Student\n";
            std::cout << "2. Teacher\n";
            std::cout << "3. Admin\n";

            const int choice = readInt("Choice: ");
            switch (choice)
            {
            case 1:
                return UserType::Student;
            case 2:
                return UserType::Teacher;
            case 3:
                return UserType::Admin;
            default:
                std::cout << "Invalid role. Try again.\n";
            }
        }
    }

    void adminMenu(AdminUser &admin)
    {
        while (true)
        {
            std::cout << "\n=== Admin menu ===\n";
            std::cout << "1. Create user\n";
            std::cout << "2. Remove user\n";
            std::cout << "3. View all users\n";
            std::cout << "4. View user details\n";
            std::cout << "5. Logout\n";

            const int choice = readInt("Choose option: ");

            if (choice == 1)
            {
                const std::string username = readString("Username: ");
                const std::string password = readString("Password: ");
                admin.addUser(username, CryptoEngine::hashPassword(password), readRoleChoice());
            }
            else if (choice == 2)
            {
                const int userId = readInt("User ID to remove: ");
                admin.removeUser(userId);
            }
            else if (choice == 3)
            {
                admin.viewAllUsers();
            }
            else if (choice == 4)
            {
                const int userId = readInt("User ID: ");
                admin.GetUserDetails(userId);
            }
            else if (choice == 5)
            {
                break;
            }
            else
            {
                std::cout << "Invalid option.\n";
            }
        }
    }

    void teacherMenu(const std::shared_ptr<TeacherUser> &teacher)
    {
        while (true)
        {
            std::cout << "\n=== Teacher menu ===\n";
            std::cout << "1. Add grade\n";
            std::cout << "2. View student grades\n";
            std::cout << "3. Logout\n";

            const int choice = readInt("Choose option: ");

            if (choice == 1)
            {
                const int studentId = readInt("Student ID: ");
                const std::string subject = readString("Subject: ");
                const double grade = readDouble("Grade: ");
                const std::string date = readString("Date (YYYY-MM-DD): ");
                teacher->addGradeForStudent(studentId, subject, grade, date);
            }
            else if (choice == 2)
            {
                const int studentId = readInt("Student ID: ");
                teacher->viewStudentGrades(studentId);
            }
            else if (choice == 3)
            {
                break;
            }
            else
            {
                std::cout << "Invalid option.\n";
            }
        }
    }

    void studentMenu(const std::shared_ptr<StudentUser> &student)
    {
        while (true)
        {
            std::cout << "\n=== Student menu ===\n";
            std::cout << "1. View grades\n";
            std::cout << "2. View profile\n";
            std::cout << "3. Logout\n";

            const int choice = readInt("Choose option: ");

            if (choice == 1)
            {
                student->viewGrades();
            }
            else if (choice == 2)
            {
                student->viewProfile();
            }
            else if (choice == 3)
            {
                break;
            }
            else
            {
                std::cout << "Invalid option.\n";
            }
        }
    }

    std::shared_ptr<User> loginUser()
    {
        const std::string username = readString("Username: ");
        const std::string password = readString("Password: ");

        const auto user = FileManager::getInstance().authenticateUser(username, password);
        if (!user)
        {
            std::cout << "Invalid username or password.\n";
            return nullptr;
        }

        std::cout << "Welcome, " << user->getUsername() << "!\n";
        return user;
    }
}

int main()
{
    ensureDefaultAdmin();

    while (true)
    {
        std::cout << "\n=== Student System ===\n";
        std::cout << "1. Login\n";
        std::cout << "2. Exit\n";

        const int action = readInt("Choose option: ");

        if (action == 1)
        {
            const auto currentUser = loginUser();
            if (!currentUser)
            {
                continue;
            }

            switch (currentUser->getUserType())
            {
            case UserType::Admin:
            {
                const auto adminUser = std::dynamic_pointer_cast<AdminUser>(currentUser);
                if (adminUser)
                {
                    adminMenu(*adminUser);
                }
                break;
            }
            case UserType::Teacher:
            {
                const auto teacherUser = std::dynamic_pointer_cast<TeacherUser>(currentUser);
                if (teacherUser)
                {
                    teacherMenu(teacherUser);
                }
                break;
            }
            case UserType::Student:
            {
                const auto studentUser = std::dynamic_pointer_cast<StudentUser>(currentUser);
                if (studentUser)
                {
                    studentMenu(studentUser);
                }
                break;
            }
            default:
                std::cout << "Unknown role.\n";
                break;
            }
        }
        else if (action == 2)
        {
            break;
        }
        else
        {
            std::cout << "Invalid option.\n";
        }
    }

    return 0;
}
