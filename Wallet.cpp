
#include <iostream>
#include "Wallet.h"

using namespace std;

Wallet::Wallet() { balance = 0.0; } 

Wallet::Wallet(string wID, string uID, double initialBalance) {
    walletID = wID;
    userID = uID;
    balance = initialBalance;
}

string Wallet::getWalletID() const { return walletID; }
string Wallet::getUserID() const { return userID; }
double Wallet::getBalance() const { return balance; }

void Wallet::deposit(double amount) {
    if (amount > 0) { 
        balance += amount;
        cout << "Successfully deposited Rs. " << amount << endl;
    } else {
        cout << "Invalid amount!" << endl; 
    }
}

bool Wallet::withdraw(double amount) {
    if (amount > 0 && balance >= amount) { 
        balance -= amount;
        return true;
    }
    cout << "Insufficient balance or invalid amount!" << endl; 
    return false;
}

string Wallet::toFileString() const
{
    return walletID + "," + userID + "," + to_string(balance);
}