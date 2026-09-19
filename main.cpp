#include <iostream>

#include "StudentUser.h"

int main()
{

    StudentUser student(1, "student1", "hashed_password", 101);
    
    student.displaymenu();

    std::cout << "Hello, World 11!" << std::endl;
    int a;
    std::cin>> a;
    std::cout<<a;
    return 0;
}
