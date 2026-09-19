#pragma once

#include <string>

class Grade
{
private:
    int studentID;
    std::string subject;
    std::string date;
    double grade;

public:
    Grade(int studentID, const std::string &subject, const std::string &date, double grade)
        : studentID(studentID), subject(subject), date(date), grade(grade) {}

    int getStudentID() const { return studentID; }
    std::string getSubject() const { return subject; }
    std::string getDate() const { return date; }
    double getGrade() const { return grade; }
};