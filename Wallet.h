#pragma once
#include <string>
using namespace std;

class Wallet
{
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
    double getBalance() const;

    // Core Functions
    void deposit(double amount);
    bool withdraw(double amount);

    // File formatting helper
    string toFileString() const;
};