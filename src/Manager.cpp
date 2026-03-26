#include "../include/Manager.h"
Manager::Manager(): User(){}
Manager::Manager(const string& username, const string& passwordHash): User(username, passwordHash){}

string Manager::getRole() const{return "Manager";}


