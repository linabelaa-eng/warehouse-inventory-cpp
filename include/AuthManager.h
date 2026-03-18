#ifndef AUTHMANAGER_H
#define AUTHMANAGER_H

#include <string>
#include <map>
using namespace std;
class User;
class AuthManager
{
private:
    map<string,User*>* users_;
    int failedAttempts_;
    void incrementFailedAttempts();
    void resetFailedAttempts();
    public:
    explicit AuthManager(map<string,User*>*);
    User* login(const string& username, const string& password);
    string hashPassword(const string& password);
    bool validateInput(const string& input);
    bool registerUser( User* user);
};


#endif