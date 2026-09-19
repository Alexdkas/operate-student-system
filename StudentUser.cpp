#include "StudentUser.h"

#include <iostream>

void StudentUser::displaymenu() const
{
    std::cout << "=== Student Menu ===\n";
    std::cout << "1. View grades\n";
    std::cout << "2. View profile\n";
}

void StudentUser::viewGrades() const
{
    std::cout << "Student record ID " << RecordID << ": view grades.\n";
}

void StudentUser::viewProfile() const
{
    std::cout << "Student record ID " << RecordID << ": view profile.\n";
}
