#include <string>

enum class UserType
{
    Student,
    Teacher,
    Admin
};

class User
{
private:
    int id;
    std::string username,hashedPassword;
    UserType userType;

public:
    User(int id, const std::string& username, const std::string& hashedPassword, UserType userType)
        : id(id), username(username), hashedPassword(hashedPassword), userType(userType) {}

    int getId() const { return id; }
    std::string getUsername() const { return username; }
    std::string getHashedPassword() const { return hashedPassword; }
    UserType getUserType() const { return userType; }

    void setUsername(const std::string& newUsername) { username = newUsername; }
    void setHashedPassword(const std::string& newHashedPassword) { hashedPassword = newHashedPassword; }
    void setUserType(UserType newUserType) { userType = newUserType; }

    virtual void displaymenu() const = 0; // Pure virtual function to display menu based on user type
    bool checkPassword(const std::string& password) const; // Function to check if the provided password matches the hashed password
};