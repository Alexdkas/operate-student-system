#include "User.h"

class TeacherUser : public User {
private:
    int RecordID; // Unique identifier for the teacher record
    std::string subject; // Subject taught by the teacher
    //map<pair<std::string,std::string>,std::vector<
public:
    TeacherUser(int id, const std::string& username, const std::string& hashedPassword, int recordID)
        : User(id, username, hashedPassword, UserType::Teacher), RecordID(recordID) {}
    void displaymenu() const override;
    void addGradeForStudent(int studentId, const std::string& subject, double grade); // Function to add a grade for a student
    void viewStudentGrades(int studentId) const; // Function to view grades for a specific student
    void viewGroupGrades(const std::string& subject) const; // Function to view grades for all students in a specific subject