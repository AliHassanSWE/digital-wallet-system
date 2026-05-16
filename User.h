#pragma once
#include <string>
using namespace std;

class User {
private:
    string userID;
    string name;
    string email;
    string password;

public:
    // Constructors
    User();
    User(string id, string n, string e, string p);

    // Getters
    string getUserID() const;
    string getName() const;
    string getPassword() const;

    // Functions
    void displayUser() const; // [cite: 81]
    string toFileString() const;
};