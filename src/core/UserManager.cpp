#include "core/UserManager.h"
#include <fstream>
#include <sstream>
#include <algorithm>

void UserManager::addUser(const User& user) {
    if (!userExists(user.username)) {
        users.push_back(user);
    }
}

void UserManager::saveToCSV(const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) return;

    for (const auto& user : users) {
        file << user.username << ","
             << user.password << ","
             << user.role << "\n";
    }
    file.close();
}

void UserManager::loadFromCSV(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        // If file doesn't exist, create default users
        users = {
            {"admin", "admin123", "Admin"},
            {"dapur", "dapur123", "Dapur"}
        };
        saveToCSV(filename);
        return;
    }

    users.clear();
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        std::stringstream ss(line);
        User user;
        std::getline(ss, user.username, ',');
        std::getline(ss, user.password, ',');
        std::getline(ss, user.role, ',');
        users.push_back(user);
    }
    file.close();
}

bool UserManager::authenticate(const std::string& username, const std::string& password, std::string& role) {
    for (const auto& user : users) {
        if (user.username == username && user.password == password) {
            role = user.role;
            return true;
        }
    }
    return false;
}

bool UserManager::userExists(const std::string& username) {
    return std::any_of(users.begin(), users.end(), [&](const User& u) {
        return u.username == username;
    });
}
