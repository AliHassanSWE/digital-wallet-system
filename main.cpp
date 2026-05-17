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
int failedAttempts = 0; // Tracks consecutive wrong PIN entries globally

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
    string name, email, inputPin; 

    cout << "Enter Name (No spaces): ";
    cin >> name;
    cout << "Enter Email: ";
    cin >> email;
    
    // Loop keeps running until a valid 5-digit numeric PIN is entered
    while (true) {
        cout << "Set 5-Digit Wallet PIN: ";
        cin >> inputPin;
        if (User::isValidPin(inputPin)) {
            break;
        }
        cout << "[!] Error: PIN must be exactly 5 numeric digits (e.g., 12345).\n" << endl;
    }

    // AUTO ID GENERATION
    string id = "U" + to_string(users.size() + 100);

    users.push_back(User(id, name, email, inputPin));
    wallets.push_back(Wallet("W" + id, id, 0.0)); // Auto create wallet

    FileManager::saveUsers(users);
    FileManager::saveWallets(wallets);

    cout << "\nRegistration Successful! Your new User ID is: " << id << "\n";
}

bool loginUser() {
    string id, inputPin;

    while (true) {
        // 1. Check if the system is already locked
        if (failedAttempts >= 10) {
            cout << "\n==================================================" << endl;
            cout << "[!!!] SECURITY ALERT: SYSTEM LOCKED!" << endl;
            cout << "10 Incorrect PIN attempts reached." << endl;
            cout << "==================================================" << endl;
            return false;
        }

        cout << "\n------------------ LOGIN PORTAL ------------------" << endl;
        cout << "Enter User ID (or type 'exit'): ";
        cin >> id;

        // 2. Simple 'exit' check to go back to the main menu
        if (id == "exit" || id == "EXIT") {
            cout << "Returning to Main Menu...\n";
            return false;
        }

        cout << "Enter 5-Digit PIN: ";
        cin >> inputPin;

        // 3. Search through registered users
        bool matchFound = false;
        for (size_t i = 0; i < users.size(); i++) {
            if (users[i].getUserID() == id && users[i].getPin() == inputPin) {
                loggedInUser = &users[i];
                activeWallet = findWallet(id);
                
                cout << "\n==================================================" << endl;
                cout << "  LOGIN SUCCESSFUL! WELCOME " << loggedInUser->getName() << endl;
                cout << "==================================================\n";
                
                failedAttempts = 0; // Reset count on success
                return true;        // Exit function completely
            }
        }

        // 4. If the loop finishes without returning, the login failed
        failedAttempts++;
        cout << "\n[!] ERROR: Invalid Credentials!" << endl; 
        cout << "Attempts Remaining: " << (10 - failedAttempts) << endl;
        
        if (failedAttempts >= 10) {
            cout << "\n==================================================" << endl;
            cout << "[!!!] MAXIMUM ATTEMPTS EXCEEDED. SYSTEM LOCKED." << endl;
            cout << "==================================================\n";
            return false;
        }
        
        cout << "--------------------------------------------------\n";
    }
}

void showSplashScreen() {
    cout << "\n\t" << string(62, '=') << endl;
    cout << "\t||                                                          ||" << endl;
    cout << "\t||             MULTI-USER DIGITAL WALLET SYSTEM             ||" << endl;
    cout << "\t||                                                          ||" << endl;
    cout << "\t" << string(62, '=') << endl;
    cout << "\t  DEVELOPED BY (PROJECT MEMBERS):" << endl;
    cout << "\t  ------------------------------" << endl;
    cout << "\t  1. Ali Hassan           |  Roll No: 25021519-119" << endl;
    cout << "\t  2. M. Shafay Nadeem     |  Roll No: 25021519-070" << endl;
    cout << "\t  3. M. Musa              |  Roll No: 25021519-111" << endl;
    cout << "\t  ------------------------------" << endl;
    cout << "\t  SECTION:       BSCS-(A)" << endl;
    cout << "\t  SUBMITTED TO:  Mam Ayesha Rashid" << endl;
    cout << "\t" << string(62, '=') << endl;
    cout << "\n\t  Press ENTER to start  the application...";
    
    cin.get(); // Pauses screen for your instructor to read it
    
    #ifdef _WIN32
        system("cls");   // Clears terminal on Windows
    #else
        system("cl ear"); // Clears terminal on Linux/Mac
    #endif
}
int main() {
    // Load Data on startup
    users = FileManager::loadUsers();
    wallets = FileManager::loadWallets();
showSplashScreen();
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