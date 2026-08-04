#include <iostream>
#include <vector>
#include <string>
#include "User.h"
#include "Wallet.h"
#include "FileManager.h"
#include <iomanip>
#include <fstream>
#include "Transaction.h"
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

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
    cout << string(54, '=') << endl;
}

void showMainMenu() { 
    drawLine();
    cout << "          MULTI-USER DIGITAL WALLET SYSTEM          \n";
    drawLine();
    cout << "  1. Register\n"; 
    cout << "  2. Login\n"; 
    cout << "  3. Forgot Password\n"; // <-- Inserted this
    cout << "  4. Exit\n";            // <-- Changed from 3 to 4
    drawLine();
    cout << "Choose an option: ";
}

void showUserMenu() { 
    drawLine();
    cout << "          WELCOME, " << loggedInUser->getName() << "!\n";
    cout << "          Balance: Rs. " << activeWallet->getBalance() << "\n";
    drawLine();
   cout << "1. Deposit Money" << endl;
cout << "2. Withdraw Money" << endl;
cout << "3. Transfer Money" << endl;
cout << "4. View Transaction History" << endl; 
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
    wallets.push_back(Wallet("W" + id, id, 0.0)); 

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
void FileManager::forgetPassword() {
    string searchUser, securityEmail, newPin;
    string fileUID, fileName, fileEmail, filePin;
    bool userFound = false;

    cout << "\n=========================================\n";
    cout << "             FORGOT PASSWORD             \n";
    cout << "=========================================\n";
    cout << "Enter your User ID: ";
    cin >> searchUser;

    ifstream infile("users.txt");
    ofstream tempfile("temp.txt");

    if (!infile) {
        cout << "Error: Could not open user database.\n";
        return;
    }

    // Reading file based on your User attributes: ID, Name, Email, Pin
    while (infile >> fileUID >> fileName >> fileEmail >> filePin) {
        if (fileUID == searchUser) {
            userFound = true;
            
            cout << "Verification: Enter your registered email address: ";
            cin >> securityEmail;

            if (securityEmail == fileEmail) {
                cout << "Identity verified successfully!\n";
                
                // Loops until user enters a valid 5-digit numeric pin matching your User.h logic
                while (true) {
                    cout << "Enter your new 5-digit PIN: ";
                    cin >> newPin;
                    if (User::isValidPin(newPin)) {
                        break;
                    }
                    cout << "Invalid PIN! Must be exactly 5 digits.\n";
                }
                
                filePin = newPin; 
                cout << "Password (PIN) updated successfully!\n";
            } else {
                cout << "Incorrect email. Access denied.\n";
            }
        }
        tempfile << fileUID << " " << fileName << " " << fileEmail << " " << filePin << "\n";
    }

    infile.close();
    tempfile.close();

    if (userFound) {
        remove("users.txt");
        rename("temp.txt", "users.txt");
    } else {
        remove("temp.txt"); 
        cout << "User ID not found in the system.\n";
    }
}
// Helper function to create a typing animation effect
// Helper function to create a typing animation effect
void typeText(const string& text, int delayMs = 15) {
    for (char c : text) {
        cout << c << flush;
        
        // Native delay handling to avoid compiler threading errors
        #ifdef _WIN32
            Sleep(delayMs); // Windows native sleep function
        #else
            usleep(delayMs * 1000); // Mac/Linux native sleep function
        #endif
    }
    cout << "\n";
}

void showSplashScreen() {
    // ANSI Color Codes for terminal styling
    const string RESET   = "\033[0m";
    const string BOLD    = "\033[1m";
    const string CYAN    = "\033[96m";
    const string GREEN   = "\033[92m";
    const string YELLOW  = "\033[93m";
    const string MAGENTA = "\033[95m";

    // Clear the screen before starting
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif

    // Top Header Banner (Instant print, no delay)
    cout << CYAN << BOLD;
    cout << "\n\t" << string(70, 'x') << "\n";
    cout << "\t||" << string(66, ' ') << "||\n";
    cout << "\t||             MULTI-USER DIGITAL WALLET SYSTEM               ||\n";
    cout << "\t||" << string(66, ' ') << "||\n";
    cout << "\t" << string(70, 'x') << "\n\n" << RESET;

    // Animated Project Team Section
    typeText("\t" + string(70, '-'), 5);
    typeText("\t                          PROJECT TEAM", 20);
    typeText("\t" + string(70, '-') + "\n", 5);

    // Group Leader Designation (Highlighted in Green)
    cout << BOLD << GREEN;
    typeText("\t  [GROUP LEADER]", 30);
    cout << RESET;
    typeText("\t  > Ali Hassan                | Roll No: 25021519-119\n", 15);

    // Team Members Designation (Highlighted in Yellow)
    cout << BOLD << YELLOW;
    typeText("\t  [TEAM MEMBERS]", 30);
    cout << RESET;
    typeText("\t  > M. Shafay Nadeem          | Roll No: 25021519-070", 15);
    typeText("\t  > M. Musa                   | Roll No: 25021519-111\n", 15);

    // Academic Details (Highlighted in Magenta)
    cout << MAGENTA;
    typeText("\t" + string(70, '-'), 5);
    typeText("\t  COURSE       : Object-Oriented Programming", 15);
    typeText("\t  SECTION      : BSCS-(A)", 15);
    typeText("\t  SUBMITTED TO : Mam Ayesha Rashid", 15);
    typeText("\t" + string(70, '-') + "\n", 5);
    cout << RESET;

    // Blinking or highlighted prompt for User Input
    cout << CYAN << BOLD;
    cout << "\t  [Press ENTER to initialize secure environment...] " << RESET;

    // Wait for the user to press Enter
    cin.get();

    // Clear terminal again before loading the main menu
    #ifdef _WIN32
        system("cls");   
    #else
        system("clear"); 
    #endif
}
int main() {
    // Load Data on startup
    users = FileManager::loadUsers();
    wallets = FileManager::loadWallets();
showSplashScreen();
    int choice;
    while (true) {if (loggedInUser == nullptr) {
            showMainMenu();
            cin >> choice;
            if (choice == 1) {
                registerUser();
            } else if (choice == 2) {
                loginUser();
            } else if (choice == 3) {
                FileManager::forgetPassword(); // <-- Triggers our new function
            } else if (choice == 4) {
                cout << "Exiting system. Goodbye!\n";
                break;                         // <-- Breaks out of the application loop safely
            } else {
                cout << "Invalid option! Please try again.\n";
            }
        }
       else {
            showUserMenu();
            cin >> choice;
            if (choice == 1) {
                double amt;
                cout << "Enter amount to deposit: ";
                cin >> amt;
                activeWallet->deposit(amt);
                FileManager::saveWallets(wallets); 
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
                
 } else if (choice == 4) { 

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
        
        // This will now match your file format flawlessly
        while (file >> tID >> tType >> amt >> sID >> rID >> d) {
            if (sID == activeWallet->getUserID() || rID == activeWallet->getUserID()) {
                
                // Print the raw fields cleanly into alignment columns
                cout << left << setw(15) << d 
                     << setw(12) << tType 
                     << setw(10) << amt;
                     
                if (tType == "Transfer") {
                    cout << sID << " to " << rID;
                } else {
                    cout << "Self Action";
                }
                cout << " | ID: " << tID << endl;
                
                found = true;
            }
        }
        
        if (!found) {
            cout << "No transactions found." << endl;
        }
        file.close();
        
        cout << "\nPress Enter to continue...";
        cin.ignore(); 
        cin.get();
    } else if (choice == 5) { 
        loggedInUser = nullptr;
        activeWallet = nullptr;
        cout << "Logged out successfully.\n";
    }
          
        }
    }
    return 0;
}
// g++ main.cpp Transaction.cpp User.cpp Wallet.cpp FileManager.cpp -o WalletSystem; .\WalletSystem.exe