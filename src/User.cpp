#include "User.h"
using namespace std;
User::User(){}
User::User(const string& username, const string& passwordHash)
    : username_(username), passwordHash_(passwordHash){}
User::~User() {}
string User::getUsername() const{return username_;}
string User::getPasswordHash() const{return passwordHash_;}
string User::getEmployeeId() const{return"";}
void User::setPasswordHash(const string &hash){passwordHash_ = hash;}


