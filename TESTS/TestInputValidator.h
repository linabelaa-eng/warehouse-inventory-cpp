#pragma once
#include "../SRC/WarehouseSystem.h"

class TestInputValidator {
private:
    WarehouseSystem ws;

public:
    bool validateString(const std::string& value, const std::string& type);
    bool validateInt(int value, bool inputValid);
    bool validateDouble(double value, bool inputValid);

    // Direct passthroughs if needed
    bool validateAisle(const std::string& s);
    bool validateShelf(const std::string& s);
    bool validateUsername(const std::string& s);
    bool validatePassword(const std::string& s);
    bool validateFilePath(const std::string& s);
};
