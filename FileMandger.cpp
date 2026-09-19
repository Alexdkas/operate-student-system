#include "FileMandger.h"

#include "AdminUser.h"
#include "StudentUser.h"
#include "TeacherUser.h"

#include <fstream>
#include <sstream>

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

    UserType stringToUserType(const std::string &value)
    {
        if (value == "Student")
        {
            return UserType::Student;
        }
        if (value == "Teacher")
        {
            return UserType::Teacher;
        }
        if (value == "Admin")
        {
            return UserType::Admin;
        }
        return UserType::Student;
    }

    std::string trim(const std::string &value)
    {
        const auto start = value.find_first_not_of(" \t\r\n");
        if (start == std::string::npos)
        {
            return "";
        }

        const auto end = value.find_last_not_of(" \t\r\n");
        return value.substr(start, end - start + 1);
    }
}

std::vector<Student> FileManager::loadStudents() const
{
    std::vector<Student> students;
    std::ifstream input(studentsFile);

    if (!input.is_open())
    {
        return students;
    }

    std::string line;
    while (std::getline(input, line))
    {
        if (line.empty())
        {
            continue;
        }

        std::stringstream stream(line);
        std::string studentId,
            name,
            surname,
            email,
            group;

        std::getline(stream, studentId, ',');
        std::getline(stream, name, ',');
        std::getline(stream, surname, ',');
        std::getline(stream, email, ',');
        std::getline(stream, group, ',');

        students.push_back(Student(std::stoi(studentId), name, surname, email, group));
    }

    return students;
}

void FileManager::addStudent(const Student &student)
{
    std::ofstream output(studentsFile, std::ios::app);
    if (output.is_open())
    {
        output << student.FileString() << '\n';
    }
}

void FileManager::updateStudent(const Student &student)
{
    std::vector<Student> students = loadStudents();
    bool found = false;

    for (auto &existing : students)
    {
        if (existing.getStudentID() == student.getStudentID())
        {
            existing.setName(student.getName());
            existing.setSurname(student.getSurname());
            existing.setEmail(student.getEmail());
            existing.setGroup(student.getGroup());
            found = true;
            break;
        }
    }

    if (!found)
    {
        students.push_back(student);
    }

    std::ofstream output(studentsFile, std::ios::trunc);
    for (const auto &item : students)
    {
        output << item.FileString() << '\n';
    }
}

void FileManager::deleteStudent(int studentID)
{
    std::vector<Student> students = loadStudents();
    std::vector<Student> filtered;

    for (const auto &student : students)
    {
        if (student.getStudentID() != studentID)
        {
            filtered.push_back(student);
        }
    }

    std::ofstream output(studentsFile, std::ios::trunc);
    for (const auto &item : filtered)
    {
        output << item.FileString() << '\n';
    }
}

std::vector<Grade> FileManager::loadGrades() const
{
    std::vector<Grade> grades;
    std::ifstream input(gradesFile);

    if (!input.is_open())
    {
        return grades;
    }

    std::string line;
    while (std::getline(input, line))
    {
        if (line.empty())
        {
            continue;
        }

        std::stringstream stream(line);
        std::string studentId, subject, date, value;

        std::getline(stream, studentId, ',');
        std::getline(stream, subject, ',');
        std::getline(stream, date, ',');
        std::getline(stream, value, ',');

        grades.push_back(Grade(std::stoi(studentId), subject, date, std::stod(value)));
    }

    return grades;
}

void FileManager::addGrade(const Grade &grade)
{
    std::ofstream output(gradesFile, std::ios::app);
    if (output.is_open())
    {
        output << grade.getStudentID() << ',' << grade.getSubject() << ',' << grade.getDate() << ',' << grade.getGrade() << '\n';
    }
}

void FileManager::updateGrade(const Grade &grade)
{
    std::vector<Grade> grades = loadGrades();
    bool found = false;

    for (auto &existing : grades)
    {
        if (existing.getStudentID() == grade.getStudentID() && existing.getSubject() == grade.getSubject())
        {
            existing = grade;
            found = true;
            break;
        }
    }

    if (!found)
    {
        grades.push_back(grade);
    }

    std::ofstream output(gradesFile, std::ios::trunc);
    for (const auto &item : grades)
    {
        output << item.getStudentID() << ',' << item.getSubject() << ',' << item.getDate() << ',' << item.getGrade() << '\n';
    }
}

void FileManager::deleteGrade(int studentID, const std::string &subject)
{
    std::vector<Grade> grades = loadGrades();
    std::vector<Grade> filtered;

    for (const auto &grade : grades)
    {
        if (grade.getStudentID() != studentID || grade.getSubject() != subject)
        {
            filtered.push_back(grade);
        }
    }

    std::ofstream output(gradesFile, std::ios::trunc);
    for (const auto &item : filtered)
    {
        output << item.getStudentID() << ',' << item.getSubject() << ',' << item.getDate() << ',' << item.getGrade() << '\n';
    }
}

std::vector<std::shared_ptr<User>> FileManager::loadUsers() const
{
    std::vector<std::shared_ptr<User>> users;
    std::ifstream input(usersFile);

    if (!input.is_open())
    {
        return users;
    }

    std::string line;
    while (std::getline(input, line))
    {
        line = trim(line);
        if (line.empty())
        {
            continue;
        }

        std::stringstream stream(line);
        std::string id, username, hashedPassword, userType, recordId;

        std::getline(stream, id, ',');
        std::getline(stream, username, ',');
        std::getline(stream, hashedPassword, ',');
        std::getline(stream, userType, ',');
        std::getline(stream, recordId, ',');

        const int numericId = std::stoi(id);
        const int numericRecordId = std::stoi(recordId);
        const UserType type = stringToUserType(userType);

        if (type == UserType::Student)
        {
            users.push_back(std::make_shared<StudentUser>(numericId, username, hashedPassword, numericRecordId));
        }
        else if (type == UserType::Teacher)
        {
            users.push_back(std::make_shared<TeacherUser>(numericId, username, hashedPassword, numericRecordId));
        }
        else
        {
            users.push_back(std::make_shared<AdminUser>(numericId, username, hashedPassword, numericRecordId));
        }
    }

    return users;
}

void FileManager::addUser(const std::shared_ptr<User> &user)
{
    std::ofstream output(usersFile, std::ios::app);
    if (output.is_open())
    {
        output << user->getId() << ',' << user->getUsername() << ',' << user->getHashedPassword() << ','
               << userTypeToString(user->getUserType()) << ',' << user->getId() << '\n';
    }
}

void FileManager::updateUser(const std::shared_ptr<User> &user)
{
    std::vector<std::shared_ptr<User>> users = loadUsers();
    bool found = false;

    for (auto &existing : users)
    {
        if (existing && existing->getId() == user->getId())
        {
            existing = user;
            found = true;
            break;
        }
    }

    if (!found)
    {
        users.push_back(user);
    }

    std::ofstream output(usersFile, std::ios::trunc);
    for (const auto &item : users)
    {
        if (item)
        {
            output << item->getId() << ',' << item->getUsername() << ',' << item->getHashedPassword() << ','
                   << userTypeToString(item->getUserType()) << ',' << item->getId() << '\n';
        }
    }
}

void FileManager::deleteUser(int userID)
{
    std::vector<std::shared_ptr<User>> users = loadUsers();
    std::vector<std::shared_ptr<User>> filtered;

    for (const auto &user : users)
    {
        if (user && user->getId() != userID)
        {
            filtered.push_back(user);
        }
    }

    std::ofstream output(usersFile, std::ios::trunc);
    for (const auto &item : filtered)
    {
        if (item)
        {
            output << item->getId() << ',' << item->getUsername() << ',' << item->getHashedPassword() << ','
                   << userTypeToString(item->getUserType()) << ',' << item->getId() << '\n';
        }
    }
}

std::shared_ptr<User> FileManager::authenticateUser(const std::string &username, const std::string &password) const
{
    const auto users = loadUsers();
    for (const auto &user : users)
    {
        if (user && user->getUsername() == username && user->checkPassword(password))
        {
            return user;
        }
    }

    return nullptr;
}
