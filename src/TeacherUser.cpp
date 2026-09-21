#include "TeacherUser.h"
#include "FileMandger.h"
#include "Logger.h"

void TeacherUser::displaymenu() const
{
    Logger::log("=== Teacher Menu ===");
    Logger::log("1. Add grade for student");
    Logger::log("2. View student grades");
    Logger::log("3. View group grades");
}

void TeacherUser::addGradeForStudent(int studentId, const std::string &subject, double grade, const std::string &date)
{
    Logger::log("Teacher adds grade " + std::to_string(grade) + " in subject '" + subject + "' for student ID " + std::to_string(studentId));

    FileManager::getInstance().addGrade(Grade(studentId, subject, date, grade));
}

void TeacherUser::viewStudentGrades(int studentId) const
{
    Logger::log("Teacher views grades for student ID " + std::to_string(studentId));
    std::vector<Grade> grades = FileManager::getInstance().getGradesForStudent(studentId);
    if (grades.empty())
    {
        Logger::log("No grades found for this student.");
    }
    else
    {
        Logger::log("Grades for student ID " + std::to_string(studentId) + ":");
        for (const auto &grade : grades)
        {
            Logger::log("Subject: " + grade.getSubject() + ", Date: " + grade.getDate() + ", Grade: " + std::to_string(grade.getGrade()));
        }
    }
}

void TeacherUser::viewGroupGrades(const std::string &subject) const
{
    Logger::log("Teacher views group grades for subject '" + subject + "'");
    std::vector<Grade> grades = FileManager::getInstance().loadGrades();
    bool found = false;
    for (const auto &grade : grades)
    {
        if (grade.getSubject() == subject)
        {
            found = true;
            Logger::log("Student ID: " + std::to_string(grade.getStudentID()) + ", Date: " + grade.getDate() + ", Grade: " + std::to_string(grade.getGrade()));
        }
    }
    if (!found)
    {
        Logger::log("No grades found for subject '" + subject + "'.");
    }
}
