#include "FileManager.h"
#include <fstream>
#include <iostream>
#include <iomanip>
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
void FileManager::generateStatement(string loggedInUserID, string loggedInUserName) {
    // ANSI Color Codes
    const string RESET = "\033[0m";
    const string BOLD = "\033[1m";
    const string CYAN = "\033[96m";
    const string GREEN = "\033[92m";
    const string YELLOW = "\033[93m";

    // 1. Setup the export file (e.g., "Statement_25021519-119.txt")
    string filename = "Statement_" + loggedInUserID + ".txt";
    ofstream outFile(filename);

    // 2. Open the transactions database
    ifstream inFile("transactions.csv");
    string tID, tType, amountStr, sender, receiver, date;
    
    // We will build the header string to print to BOTH the console and the file
    string header = 
        "\n\t=======================================================\n"
        "\t           OFFICIAL TRANSACTION STATEMENT\n"
        "\t=======================================================\n"
        "\t Account Holder : " + loggedInUserName + "\n"
        "\t Account ID     : " + loggedInUserID + "\n"
        "\t-------------------------------------------------------\n"
        "\t TYPE      | AMOUNT    | DETAILS             | DATE\n"
        "\t-------------------------------------------------------\n";

    // Print header to terminal (with colors)
    cout << CYAN << BOLD << header << RESET;
    
    // Print header to text file (no colors, just raw text)
    if(outFile.is_open()) {
        outFile << "=======================================================\n";
        outFile << "           OFFICIAL TRANSACTION STATEMENT\n";
        outFile << "=======================================================\n";
        outFile << " Account Holder : " << loggedInUserName << "\n";
        outFile << " Account ID     : " << loggedInUserID << "\n";
        outFile << "-------------------------------------------------------\n";
        outFile << left << setw(11) << " TYPE" << "| " 
                << setw(10) << "AMOUNT" << "| " 
                << setw(20) << "DETAILS" << "| " 
                << "DATE\n";
        outFile << "-------------------------------------------------------\n";
    }

    // 3. Read the CSV and filter transactions for THIS specific user
    bool hasTransactions = false;
    while (getline(inFile, tID, ',') && getline(inFile, tType, ',') && 
           getline(inFile, amountStr, ',') && getline(inFile, sender, ',') && 
           getline(inFile, receiver, ',') && getline(inFile, date)) {
        
        // Only process transactions where the user is the sender or receiver
        if (sender == loggedInUserID || receiver == loggedInUserID) {
            hasTransactions = true;
            
            // Format for terminal (Green amounts)
            cout << "\t " << left << setw(10) << tType << "| "
                 << GREEN << "Rs. " << setw(6) << amountStr << RESET << "| "
                 << setw(20) << (sender == loggedInUserID ? "To: " + receiver : "From: " + sender) << "| "
                 << date << "\n";

            // Format for Text File
            if(outFile.is_open()) {
                outFile << " " << left << setw(10) << tType << "| "
                        << "Rs. " << setw(6) << amountStr << "| "
                        << setw(20) << (sender == loggedInUserID ? "To: " + receiver : "From: " + sender) << "| "
                        << date << "\n";
            }
        }
    }

    if (!hasTransactions) {
        cout << "\t " << YELLOW << "No transactions found for this account.\n" << RESET;
        if(outFile.is_open()) outFile << " No transactions found for this account.\n";
    }

    // 4. Close out the borders
    string footer = "\t=======================================================\n";
    cout << CYAN << BOLD << footer << RESET;
    cout << "\n\t " << GREEN << "[SUCCESS]" << RESET << " Statement saved to computer as: " << filename << "\n";
    
    if(outFile.is_open()) {
        outFile << "=======================================================\n";
        outFile << "             Thank you for using our system.\n";
        outFile.close();
    }
    inFile.close();
}