#include "AuthManager.h"
#include "User.h"
#include <iostream>
#include <algorithm>
#include <numeric>
#include <cstdlib>
#include <functional>
using namespace std;
AuthManager::AuthManager(map<string, User*>* users):users_(users),failedAttempts_(0){}
string AuthManager::hashPassword(const string& password) {
    unsigned long long hash = 5381;
    for (unsigned char c : password)
        hash = hash * 33 + c;
    return to_string(hash);
}
bool AuthManager::validateInput(const string& input) {
    if (input.empty()) return false;

    for (char c : input) {
        if (c == ',' || c == '\n' || c == '\r')
            return false;
    }

    return true;
}

void AuthManager::incrementFailedAttempts() {
    ++failedAttempts_;
    if (failedAttempts_ >= 3) {
        cout << "Too many failed login attempts. System shutting down.\n";
        exit(1);
    }
}

void AuthManager::resetFailedAttempts() { failedAttempts_ = 0; }
User* AuthManager::login(const string& username, const string& password) {
    if (!users_) return nullptr;
    auto it = users_->find(username);
    if (it == users_->end()) { incrementFailedAttempts(); return nullptr; }
    if (!it->second) { incrementFailedAttempts(); return nullptr; }
    string hashed = hashPassword(password);
    if (it->second->getPasswordHash() != hashed) { incrementFailedAttempts(); return nullptr; }
    resetFailedAttempts();
    return it->second;
}

bool AuthManager::registerUser(User* user) {
    if (!users_ || !user || !validateInput(user->getUsername())) return false;
    auto it = users_->find(user->getUsername());
    if (it != users_->end() && it->second) { delete it->second; }
    (*users_)[user->getUsername()] = user;
    return true;
}

