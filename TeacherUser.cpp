#include "TeacherUser.h"

#include <iostream>

void TeacherUser::displaymenu() const
{
    std::cout << "=== Teacher Menu ===\n";
    std::cout << "1. Add grade for student\n";
    std::cout << "2. View student grades\n";
    std::cout << "3. View group grades\n";
}

void TeacherUser::addGradeForStudent(int studentId, const std::string &subject, double grade)
{
    std::cout << "Teacher adds grade " << grade << " in subject '" << subject << "' for student ID " << studentId << '\n';
}

void TeacherUser::viewStudentGrades(int studentId) const
{
    std::cout << "Teacher views grades for student ID " << studentId << '\n';
}

void TeacherUser::viewGroupGrades(const std::string &subject) const
{
    std::cout << "Teacher views group grades for subject '" << subject << "'\n";
}
