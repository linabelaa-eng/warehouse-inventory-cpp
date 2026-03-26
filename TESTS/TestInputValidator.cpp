
#include "TestInputValidator.h"



// Route string validations
bool TestInputValidator::validateString(const std::string& value, const std::string& type) {
    if (type == "Product ID" || type == "Employee ID" || type == "Order ID") {
        return ws.validateId(value, type);
    }
    if (type == "Product name") {
        return ws.validateName(value, type);
    }
    return false;
}

// Route int validations
bool TestInputValidator::validateInt(int value, bool inputValid) {
    return ws.validateQuantity(value, inputValid);
}

// Route double validations
bool TestInputValidator::validateDouble(double value, bool inputValid) {
    return ws.validatePrice(value, inputValid);
}

// Direct passthroughs
bool TestInputValidator::validateAisle(const std::string& s) {
    return ws.validateAisle(s);
}

bool TestInputValidator::validateShelf(const std::string& s) {
    return ws.validateShelf(s);
}

bool TestInputValidator::validateUsername(const std::string& s) {
    return ws.validateUsername(s);
}

bool TestInputValidator::validatePassword(const std::string& s) {
    return ws.validatePassword(s);
}

bool TestInputValidator::validateFilePath(const std::string& s) {
    return ws.validateFilePath(s);
}
