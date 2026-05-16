#include <iostream>
#include <vector>
#include <string>
#include "User.h"
#include "Wallet.h"
#include "FileManager.h"
#include <iomanip>
#include <fstream>
#include "Transaction.h"

using namespace std;

// Global Data Vectors
vector<User> users;
vector<Wallet> wallets;
User* loggedInUser = nullptr;
Wallet* activeWallet = nullptr;

// Helper to find wallet by userID
Wallet* findWallet(string uID) {
    for (int i = 0; i < wallets.size(); i++) {
        if (wallets[i].getUserID() == uID) {
            return &wallets[i];
        }
    }
    return nullptr;
}

void drawLine() {
    cout << "====================================================\n";
}

void showMainMenu() { // [cite: 129]
    drawLine();
    cout << "          MULTI-USER DIGITAL WALLET SYSTEM          \n";
    drawLine();
    cout << "  1. Register\n"; // [cite: 130]
    cout << "  2. Login\n"; // [cite: 131]
    cout << "  3. Exit\n"; // [cite: 132]
    drawLine();
    cout << "Choose an option: ";
}

void showUserMenu() { // [cite: 133]
    drawLine();
    cout << "          WELCOME, " << loggedInUser->getName() << "!\n";
    cout << "          Balance: Rs. " << activeWallet->getBalance() << "\n";
    drawLine();
   cout << "1. Deposit Money" << endl;
cout << "2. Withdraw Money" << endl;
cout << "3. Transfer Money" << endl;
cout << "4. View Transaction History" << endl; // New Option
cout << "5. Logout" << endl;
    drawLine();
    cout << "Choose an option: ";
}

void registerUser() {
    string name, email, pass; // Notice we don't ask for 'id' here anymore

    cout << "Enter Name (No spaces): ";
    cin >> name;
    cout << "Enter Email: ";
    cin >> email;
    cout << "Enter Password: ";
    cin >> pass;

    // --- AUTO ID GENERATION ---
    // If there are 0 users, size is 0. 0 + 100 = 100. So the ID becomes "U100".
    // Next user will be "U101", then "U102", etc.
    string id = "U" + to_string(users.size() + 100);

    users.push_back(User(id, name, email, pass));
    wallets.push_back(Wallet("W" + id, id, 0.0)); // Auto create wallet

    FileManager::saveUsers(users);
    FileManager::saveWallets(wallets);
    
    // Tell the user what their new auto-generated ID is!
    cout << "\nRegistration Successful! Your new User ID is: " << id << "\n";
  
    users.push_back(User(id, name, email, pass));
    wallets.push_back(Wallet("W" + id, id, 0.0)); // Auto create wallet [cite: 29]
    
    FileManager::saveUsers(users);
    FileManager::saveWallets(wallets);
    cout << "\nRegistration Successful! Wallet Created.\n";
}

bool loginUser() {
    string id, pass;
    cout << "Enter User ID: ";
    cin >> id;
    cout << "Enter Password: ";
    cin >> pass;

    for (int i = 0; i < users.size(); i++) {
        if (users[i].getUserID() == id && users[i].getPassword() == pass) {
            loggedInUser = &users[i];
            activeWallet = findWallet(id);
            cout << "\nLogin Successful!\n";
            return true;
        }
    }
    cout << "\nError: Invalid login credentials!\n"; // [cite: 140, 141]
    return false;
}

int main() {
    // Load Data on startup
    users = FileManager::loadUsers();
    wallets = FileManager::loadWallets();

    int choice;
    while (true) {
        if (loggedInUser == nullptr) {
            showMainMenu();
            cin >> choice;
            if (choice == 1) registerUser();
            else if (choice == 2) loginUser();
            else if (choice == 3) {
                cout << "Exiting system. Goodbye!\n";
                break;
            }
        } else {
            showUserMenu();
            cin >> choice;
            if (choice == 1) {
                double amt;
                cout << "Enter amount to deposit: ";
                cin >> amt;
                activeWallet->deposit(amt);
                FileManager::saveWallets(wallets); // Save instantly
            } else if (choice == 2) {
                double amt;
                cout << "Enter amount to withdraw: ";
                cin >> amt;
                if(activeWallet->withdraw(amt)) {
                    FileManager::saveWallets(wallets);
                    cout << "Withdrawal Successful!\n";
                }
            } else if (choice == 3) {
                string recID;
                double amt;
                cout << "Enter Receiver User ID: ";
                cin >> recID;
                Wallet* recWallet = findWallet(recID);
                
                if (recWallet == nullptr) {
                    cout << "Receiver not found!\n";
                } else {
                    cout << "Enter amount to transfer: ";
                    cin >> amt;
                    if (activeWallet->withdraw(amt)) {
                        recWallet->deposit(amt);
                        FileManager::saveWallets(wallets);
                        FileManager::logTransaction("T101", "Transfer", amt, activeWallet->getUserID(), recWallet->getUserID(), "Today");
                        cout << "Transfer Successful!\n";
                    }
                }
                // Change this section (Starting around Line 159)
    } else if (choice == 4) { 
        // --- NEW HISTORY LOGIC ---
        cout << "\n================= TRANSACTION HISTORY =================" << endl;
        cout << left << setw(15) << "Date" 
             << setw(12) << "Type" 
             << setw(10) << "Amount" 
             << "Details" << endl;
        cout << string(55, '-') << endl;

        ifstream file("transactions.txt");
        string tID, tType, sID, rID, d;
        double amt;

        bool found = false;
        while (file >> tID >> tType >> amt >> sID >> rID >> d) {
            if (sID == activeWallet->getUserID() || rID == activeWallet->getUserID()) {
                Transaction temp(tID, tType, amt, sID, rID, d);
                temp.displayTransaction();
                found = true;
            }
        }
        if (!found) cout << "No transactions found." << endl;
        file.close();
        
        cout << "\nPress Enter to continue...";
        cin.ignore(); cin.get();

    } else if (choice == 5) { // Shift Logout to Choice 5
        loggedInUser = nullptr;
        activeWallet = nullptr;
        cout << "Logged out successfully.\n";
    }
          
        }
    }
    return 0;
}
// g++ main.cpp Transaction.cpp User.cpp Wallet.cpp FileManager.cpp -o WalletSystem; .\WalletSystem.exe