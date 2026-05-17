#include "FileManager.h"
#include <fstream>
#include <iostream>
#include <iomanip>

using namespace std;

void FileManager::saveUsers(const vector<User> &users)
{

    ofstream file("users.txt");
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
    ifstream file("users.txt");
    string id, name, email, pass;
    while (file >> id >> name >> email >> pass)
    {
        users.push_back(User(id, name, email, pass));
    }
    file.close();
    return users;
}

void FileManager::saveWallets(const vector<Wallet> &wallets)
{
    ofstream file("wallets.txt");
    for (const Wallet &w : wallets)
    {
        file << w.toFileString() << endl;
    }
    file.close();
}

vector<Wallet> FileManager::loadWallets()
{
    vector<Wallet> wallets;
    ifstream file("wallets.txt");
    string wID, uID;
    double bal;
    while (file >> wID >> uID >> bal)
    {
        wallets.push_back(Wallet(wID, uID, bal));
    }
    file.close();
    return wallets;
}

// Append a single transaction
void FileManager::logTransaction(string tID, string tType, double amount, string sender, string receiver, string date) {
    ofstream file("transactions.txt", ios::app);
    if (file.is_open()) {
        
        file << tID << " " << tType << " " << amount << " " << sender << " " << receiver << " " << date << endl;
        file.close();
    }
}