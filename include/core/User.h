#ifndef USER_H
#define USER_H

#include <string>

struct User {
    std::string username;
    std::string password;
    std::string role; // "Admin" or "Dapur"
};

#endif // USER_H
