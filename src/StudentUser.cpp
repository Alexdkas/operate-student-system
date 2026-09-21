#include "StudentUser.h"

#include "FileMandger.h"
#include "Logger.h"
#include "Student.h"

#include <vector>

void StudentUser::displaymenu() const
{
    Logger::log("=== Student Menu ===");
    Logger::log("1. View grades");
    Logger::log("2. View profile");
}

void StudentUser::viewGrades() const
{
    Logger::log("Student record ID " + std::to_string(RecordID) + ": view grades.");
    std::vector<Grade> grades = FileManager::getInstance().getGradesForStudent(RecordID);
    if (grades.empty())
    {
        Logger::log("No grades found for this student.");
    }
    else
    {
        Logger::log("Grades for student record ID " + std::to_string(RecordID) + ":");
        for (const auto &grade : grades)
        {
            Logger::log("Subject: " + grade.getSubject() + ", Date: " + grade.getDate() + ", Grade: " + std::to_string(grade.getGrade()));
        }
    }
}

void StudentUser::viewProfile() const
{
    Logger::log("Student record ID " + std::to_string(RecordID) + ": view profile.");
    std::vector<Student> students = FileManager::getInstance().getStudentsByID(RecordID);
    if (students.empty())
    {
        Logger::log("No student found with this record ID.");
    }
    else
    {
        const Student &student = students.front();
        Logger::log("Profile for student record ID " + std::to_string(RecordID) + ":");
        Logger::log("Name: " + student.getName() + " " + student.getSurname());
        Logger::log("Email: " + student.getEmail());
        Logger::log("Group: " + student.getGroup());
    }
}
