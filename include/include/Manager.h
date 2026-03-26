#ifndef MANAGER_H
#define MANAGER_H

#include "User.h"

class Manager : public User {
public:
    Manager();
    Manager(const string& username, const string& passwordHash);
    string getRole() const override;
};
#endif