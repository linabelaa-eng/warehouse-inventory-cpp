#include "../include/WarehouseSystem.h"
#include <iostream>
#include <algorithm>
#include <cctype>
using namespace std;

// ── helpers ───────────────────────────────────────────────────────────────────

static bool hasInvalidChars(const string& s) {
    for (char c : s)
        if (c == ',' || c == '\n' || c == '\r' || c == '"' || c == '\\')
            return true;
    return false;
}

static bool isAlphaNumericWithAllowed(const string& s, const string& allowed) {
    for (char c : s)
        if (!isalnum(static_cast<unsigned char>(c)) &&
            allowed.find(c) == string::npos)
            return false;
    return true;
}

static bool isThreeDigits(const string& s, size_t offset) {
    if (s.size() != offset + 3) return false;
    for (size_t i = offset; i < s.size(); ++i)
        if (!isdigit(static_cast<unsigned char>(s[i]))) return false;
    return true;
}

// ── ID validators ─────────────────────────────────────────────────────────────
//
//  Product ID  : P   + 3 digits  ->  P001 .. P999
//  Employee ID : E   + 3 digits  ->  E001 .. E999
//  Order ID    : ORD + 3 digits  ->  ORD001 .. ORD999

bool WarehouseSystem::validateId(const string& id, const string& label) {
    if (id.empty()) {
        cerr << "  " << label << " cannot be empty.\n";
        return false;
    }

    if (label == "Product ID") {
        if (id[0] == 'P' && isThreeDigits(id, 1))
            return true;
        cerr << "  Invalid Product ID '" << id << "'.\n"
             << "  Format: P followed by 3 digits (e.g. P001, P042, P100).\n";
        return false;
    }

    if (label == "Employee ID") {
        if (id[0] == 'E' && isThreeDigits(id, 1))
            return true;
        cerr << "  Invalid Employee ID '" << id << "'.\n"
             << "  Format: E followed by 3 digits (e.g. E001, E025, E050).\n";
        return false;
    }

    if (label == "Order ID") {
        if (id.size() >= 3 &&
            id[0] == 'O' && id[1] == 'R' && id[2] == 'D' &&
            isThreeDigits(id, 3))
            return true;
        cerr << "  Invalid Order ID '" << id << "'.\n"
             << "  Format: ORD followed by 3 digits (e.g. ORD001, ORD067, ORD099).\n";
        return false;
    }

    cerr << "  " << label << " is invalid.\n";
    return false;
}

// ── other validators ──────────────────────────────────────────────────────────

bool WarehouseSystem::validateName(const string& name, const string& label) {
    if (name.empty()) {
        cerr << "  " << label << " cannot be empty.\n";
        return false;
    }
    if (name.size() > 60) {
        cerr << "  " << label << " must be 60 characters or fewer.\n";
        return false;
    }
    if (hasInvalidChars(name)) {
        cerr << "  " << label << " cannot contain commas, quotes, or newlines.\n";
        return false;
    }
    return true;
}

bool WarehouseSystem::validateQuantity(int qty, bool inputValid) {
    if (!inputValid) {
        cerr << "  Please enter a valid whole number for quantity.\n";
        return false;
    }
    if (qty < 0) {
        cerr << "  Quantity cannot be negative.\n";
        return false;
    }
    if (qty > 999999) {
        cerr << "  Quantity cannot exceed 999,999.\n";
        return false;
    }
    return true;
}

bool WarehouseSystem::validatePrice(double price, bool inputValid) {
    if (!inputValid) {
        cerr << "  Please enter a valid number for price (e.g. 9.99).\n";
        return false;
    }
    if (price < 0.0) {
        cerr << "  Price cannot be negative.\n";
        return false;
    }
    if (price > 999999.99) {
        cerr << "  Price cannot exceed 999,999.99.\n";
        return false;
    }
    return true;
}

bool WarehouseSystem::validateAisle(const string& aisle) {
    if (aisle.empty()) {
        cerr << "  Aisle cannot be empty.\n";
        return false;
    }
    if (aisle.size() > 10) {
        cerr << "  Aisle must be 10 characters or fewer.\n";
        return false;
    }
    if (!isAlphaNumericWithAllowed(aisle, "-")) {
        cerr << "  Aisle may only contain letters, digits, and hyphens (e.g. A1, B2).\n";
        return false;
    }
    return true;
}

bool WarehouseSystem::validateShelf(const string& shelf) {
    if (shelf.empty()) {
        cerr << "  Shelf cannot be empty.\n";
        return false;
    }
    if (shelf.size() > 10) {
        cerr << "  Shelf must be 10 characters or fewer.\n";
        return false;
    }
    if (!isAlphaNumericWithAllowed(shelf, "-")) {
        cerr << "  Shelf may only contain letters, digits, and hyphens (e.g. S1, S3).\n";
        return false;
    }
    return true;
}

bool WarehouseSystem::validateUsername(const string& username) {
    if (username.empty()) {
        cerr << "  Username cannot be empty.\n";
        return false;
    }
    if (username.size() < 3) {
        cerr << "  Username must be at least 3 characters.\n";
        return false;
    }
    if (username.size() > 30) {
        cerr << "  Username must be 30 characters or fewer.\n";
        return false;
    }
    if (!isAlphaNumericWithAllowed(username, "_")) {
        cerr << "  Username may only contain letters, digits, and underscores.\n";
        return false;
    }
    return true;
}

bool WarehouseSystem::validatePassword(const string& password) {
    if (password.empty()) {
        cerr << "  Password cannot be empty.\n";
        return false;
    }
    if (password.size() < 4) {
        cerr << "  Password must be at least 4 characters.\n";
        return false;
    }
    if (password.size() > 50) {
        cerr << "  Password must be 50 characters or fewer.\n";
        return false;
    }
    if (hasInvalidChars(password)) {
        cerr << "  Password cannot contain commas, quotes, or newlines.\n";
        return false;
    }
    return true;
}

bool WarehouseSystem::validateFilePath(const string& path) {
    if (path.empty()) {
        cerr << "  File path cannot be empty.\n";
        return false;
    }
    if (path.size() > 260) {
        cerr << "  File path is too long.\n";
        return false;
    }
    for (char c : path) {
        if (c == '"' || c == '\'' || c == '\n' || c == '\r' || c == '\0') {
            cerr << "  File path contains invalid characters.\n";
            return false;
        }
    }
    return true;
}