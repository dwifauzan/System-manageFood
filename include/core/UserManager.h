#ifndef USER_MANAGER_H
#define USER_MANAGER_H

#include "User.h"
#include <vector>
#include <string>

class UserManager {
public:
    void addUser(const User& user);
    std::vector<User> getUsers() const { return users; }
    
    void saveToCSV(const std::string& filename);
    void loadFromCSV(const std::string& filename);
    
    bool authenticate(const std::string& username, const std::string& password, std::string& role);
    bool userExists(const std::string& username);

private:
    std::vector<User> users;
};

#endif // USER_MANAGER_H
