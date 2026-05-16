
#include <iostream>
#include "Wallet.h"

Wallet::Wallet() { balance = 0.0; } // [cite: 60]

Wallet::Wallet(string wID, string uID, double initialBalance) {
    walletID = wID;
    userID = uID;
    balance = initialBalance;
}

string Wallet::getWalletID() const { return walletID; }
string Wallet::getUserID() const { return userID; }
double Wallet::getBalance() const { return balance; }

void Wallet::deposit(double amount) {
    if (amount > 0) { // [cite: 62]
        balance += amount;
        cout << "Successfully deposited Rs. " << amount << endl;
    } else {
        cout << "Invalid amount!" << endl; // [cite: 143]
    }
}

bool Wallet::withdraw(double amount) {
    if (amount > 0 && balance >= amount) { // [cite: 64, 65]
        balance -= amount;
        return true;
    }
    cout << "Insufficient balance or invalid amount!" << endl; // [cite: 142]
    return false;
}

string Wallet::toFileString() const {
    return walletID + " " + userID + " " + to_string(balance); // [cite: 120, 121]
}