#include "User.h"
#include <iostream>

User::User() {}

User::User(string id, string n, string e, string p) {
    userID = id;
    name = n;
    email = e;
    pin = p;
}

string User::getUserID() const { return userID; }
string User::getName() const { return name; }
string User::getPin() const { return pin; }

void User::displayUser() const {
    cout << "User ID: " << userID << " | Name: " << name << " | Email: " << email << endl;
}

string User::toFileString() const {
    return userID + " " + name + " " + email + " " + pin; // [cite: 118, 119]
}