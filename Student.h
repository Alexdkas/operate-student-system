#pragma once

#include <string>

class Student
{
private:
    int studentID;
    std::string name, surname;
    std::string email;
    std::string group;

public:
    Student(int studentID, const std::string &name, const std::string &surname, const std::string &email, const std::string &group)
        : studentID(studentID), name(name), surname(surname), email(email), group(group) {}

    int getStudentID() const { return studentID; }
    std::string getName() const { return name; }
    std::string getSurname() const { return surname; }
    std::string getEmail() const { return email; }
    std::string getGroup() const { return group; }

    std::string FileString() const
    {
        return std::to_string(studentID) + "," + name + "," + surname + "," + email + "," + group;
    }

    void setName(const std::string &newName) { name = newName; }
    void setSurname(const std::string &newSurname) { surname = newSurname; }
    void setEmail(const std::string &newEmail) { email = newEmail; }
    void setGroup(const std::string &newGroup) { group = newGroup; }
};