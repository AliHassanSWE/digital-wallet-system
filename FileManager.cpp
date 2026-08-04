#include "FileManager.h"
#include <fstream>
#include <iostream>
#include <iomanip>

using namespace std;

void FileManager::saveUsers(const vector<User> &users)
{
    ofstream file("users.csv");
    if (file.is_open())
    {
        for (const auto &u : users)
        {
            file << u.toFileString() << endl;
        }
        file.close();
    }
}

// Load users from file
vector<User> FileManager::loadUsers()
{
    vector<User> users;
    ifstream file("users.csv");
    string id, name, email, pass;
    
    // Parse using commas instead of spaces
    while (getline(file, id, ',') && getline(file, name, ',') && getline(file, email, ',') && getline(file, pass))
    {
        users.push_back(User(id, name, email, pass));
    }
    
    file.close();
    return users;
}

void FileManager::saveWallets(const vector<Wallet> &wallets)
{
    ofstream file("wallets.csv");
    for (const Wallet &w : wallets)
    {
        file << w.toFileString() << endl;
    }
    file.close();
}

vector<Wallet> FileManager::loadWallets()
{
    vector<Wallet> wallets;
    ifstream file("wallets.csv");
    string wID, uID, balStr;
    
    // Parse strings with commas, then convert the balance string to a double
    while (getline(file, wID, ',') && getline(file, uID, ',') && getline(file, balStr))
    {
        double bal = stod(balStr);
        wallets.push_back(Wallet(wID, uID, bal));
    }
    
    file.close();
    return wallets;
}

// Append a single transaction
void FileManager::logTransaction(string tID, string tType, double amount, string sender, string receiver, string date) {
    ofstream file("transactions.csv", ios::app);
    if (file.is_open()) {
        file << tID << "," << tType << "," << amount << "," << sender << "," << receiver << "," << date << endl;
        file.close();
    }
}