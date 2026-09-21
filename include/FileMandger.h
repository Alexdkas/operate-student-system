#pragma once

#include <memory>
#include <string>
#include <vector>

#include "Grade.h"
#include "User.h"

class Student;

class FileManager
{
private:
    const std::string studentsFile = "data/students.txt";
    const std::string gradesFile = "data/grades.txt";
    const std::string usersFile = "data/users.txt";

public:
    static FileManager &getInstance();

    std::vector<Student> loadStudents() const;                 // Function to load students from the file
    void addStudent(const Student &student);                   // Function to add a new student to the file
    void updateStudent(const Student &student);                // Function to update an existing student's information in the file
    void deleteStudent(int studentID);                         // Function to delete a student from the file by
    std::vector<Student> getStudentsByID(int studentID) const; // Function to get students by ID

    std::vector<Grade> loadGrades() const;                       // Function to load grades from the file
    void addGrade(const Grade &grade);                           // Function to add a new grade to the file
    void updateGrade(const Grade &grade);                        // Function to update an existing grade in the file
    void deleteGrade(int studentID, const std::string &subject); // Function to delete
    std::vector<Grade> getGradesForStudent(int studentID) const; // Function to get all grades for a specific student

    std::vector<std::shared_ptr<User>> loadUsers() const; // Function to load users from the file
    void addUser(const std::shared_ptr<User> &user);      // Function to add a new user to the file
    void updateUser(const std::shared_ptr<User> &user);   // Function to update an existing user's information in the file
    void deleteUser(int userID);                          // Function to delete a user from the file by ID

    std::shared_ptr<User> authenticateUser(const std::string &username, const std::string &password) const; // Function to authenticate a user based on username and password
};