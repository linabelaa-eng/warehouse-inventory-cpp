#ifndef USER_H
#define USER_H

#include <string>
using namespace std;
class User
{
    protected:
    string username_;
    string passwordHash_;
    public:
    User();
    User(const std::string& username, const std::string& passwordHash);
    virtual ~User();
    string getUsername() const;
    string getPasswordHash() const;
    virtual string getRole() const = 0;
    virtual string getEmployeeId() const;
    void setPasswordHash(const string &hash);
};
#endif