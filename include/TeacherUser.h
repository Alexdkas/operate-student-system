#pragma once

#include "User.h"

#include <string>

class TeacherUser : public User
{
private:
    int RecordID;        // Unique identifier for the teacher record
    std::string subject; // Subject taught by the teacher

public:
    TeacherUser(int id, const std::string &username, const std::string &hashedPassword, int recordID)
        : User(id, username, hashedPassword, UserType::Teacher), RecordID(recordID) {}

    void displaymenu() const override;
    void addGradeForStudent(int studentId, const std::string &subject, double grade, const std::string &date); // Function to add a grade for a student
    void viewStudentGrades(int studentId) const;                                      // Function to view grades for a specific student
    void viewGroupGrades(const std::string &subject) const;                           // Function to view grades for all students in a specific subject
};