#pragma once
#include <string>
using namespace std;

class User {
private:
    string userID;
    string name;
    string email;
    string pin;

public:
    // Constructors
    User();
    User(string id, string n, string e, string p);

    // Getters
    string getUserID() const;
    string getName() const;
    string getPin() const;

    // Functions
    void displayUser() const; 
    string toFileString() const;
    static bool isValidPin(const string& inputPin) {
        if (inputPin.length() != 5) return false;
        for (char c : inputPin) {
            if (!isdigit(c)) return false; 
        }
        return true;
    }
};