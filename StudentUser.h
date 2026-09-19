#include "User.h"

class StudentUser : public User
{

private:
    int RecordID; // Unique identifier for the student record
public:
    StudentUser(int id, const std::string& username, const std::string& hashedPassword, int recordID)
        : User(id, username, hashedPassword, UserType::Student), RecordID(recordID) {}

    void displaymenu() const override;
    void viewGrades() const; // Function to view grades for the student
    void viewProfile() const; // Function to view the student's profile
};