#pragma once
#include <string>
using namespace std;

class Wallet {
private:
    string walletID;
    string userID;
    double balance;

public:
    // Constructors
    Wallet();
    Wallet(string wID, string uID, double initialBalance);

    // Getters
    string getWalletID() const;
    string getUserID() const;
    double getBalance() const; // [cite: 66, 67]

    // Core Functions
    void deposit(double amount); // [cite: 61]
    bool withdraw(double amount); // [cite: 63, 64]
    
    // File formatting helper
    string toFileString() const;
};