#include "Student.h"

#include "FileMandger.h"

std::vector<Grade> Student::getGrades() const
{
    return FileManager::getInstance().getGradesForStudent(studentID);
}
