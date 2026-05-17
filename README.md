# Multi-User Digital Wallet System – OOP Final Project

A complete console-based Digital Wallet System built in C++ that simulates a real-world e-wallet application. This project strictly utilizes Object-Oriented Programming (OOP) principles and file handling (`fstream`) to permanently store user data, wallets, and transaction histories. 

=========================

## Student Information

* **Project Members:**
  * Ali Hassan           |  Roll No.: 25021519-119
  * M. Shafay Nadeem     |  Roll No.: 25021519-070
  * M. Musa              |  Roll No.: 25021519-111
* **Section:** BSCS-(A)
* **Department:** BS Computer Science, University of Gujrat (UOG)
* **Instructor:** Mam Ayesha Rashid

=========================

## Project Overview

This project demonstrates core programming concepts including **Classes & Objects, Encapsulation, File I/O, Loops, and Conditional Logic**. It serves as a secure digital wallet environment where users can create accounts, manage balances, and seamlessly transfer funds to other registered users within the system.

## Key Features & Menu Options

### 1. Main Menu (Entry Portal)
* **Register:** Allows new users to create an account. 
  * Collects Name and Email.
  * **PIN Validation:** Enforces a strict 5-digit numeric PIN for security.
  * Auto-generates a unique User ID (e.g., `U100`, `U101`).
* **Login:** Grants access to the user dashboard.
  * Requires valid User ID and 5-digit PIN.
  * **Security Lockout:** Features an automatic security protocol that locks the system after 10 consecutive incorrect PIN attempts.
* **Exit:** Safely closes the application.

### 2. User Dashboard (Post-Login)
Once verified, users have access to their personal wallet dashboard containing the following options:
* **Deposit Money:** Users can instantly add funds to their wallet balance. The file database updates in real-time.
* **Withdraw Money:** Allows users to deduct funds from their wallet. Includes validation to prevent withdrawing more than the current available balance.
* **Transfer Money:** A peer-to-peer transaction feature. 
  * Prompts for a Receiver ID and validates if the receiver exists in the database.
  * Deducts the amount from the sender and adds it to the receiver simultaneously.
* **View Transaction History:** Reads from the transaction log to display a beautifully formatted table of all past activities (Deposits, Withdrawals, Transfers) specific to the logged-in user.
* **Logout:** Clears the active session and returns the user safely to the Main Menu.

=========================

## Data Storage (Text File Structure)

This project relies on three primary `.txt` databases to maintain state across sessions. 

* `users.txt`: Stores all user credentials. Format: `[UserID] [Name] [Email] [5-Digit PIN]`
* `wallets.txt`: Links directly to the user to store balances. Format: `[WalletID] [OwnerID] [CurrentBalance]`
* `transactions.txt`: A comprehensive ledger of all system movements. Format: `[TransactionID] [Type] [Amount] [SenderID] [ReceiverID] [Date]`

### Note on .gitignore
If you clone this repository, you may notice that `.txt` and `.exe` files are missing. This is intentional:
1. **`.txt` files:** Ignored for privacy. Running the program for the first time will automatically generate clean database files on your local machine.
2. **`.exe` files:** Ignored to force a fresh compilation on your system, preventing runtime errors from mismatched OS environments.

=========================

## How to Run

This project consists of multiple interconnected C++ source files (`main.cpp`, `FileManager.cpp`, `Transaction.cpp`, `User.cpp`, `Wallet.cpp`) and their respective header files that must be compiled together.

### Method 1: Using `run.bat` (Recommended for Windows)

Included in the repository is a Windows Batch file named `run.bat`. This script automates the entire build process.

1. Navigate to the project folder in your File Explorer.
2. Double-click the `run.bat` file.
3. The script will automatically:
   * Compile all `.cpp` files together using the `g++` compiler.
   * Link the output into a single executable file.
   * Launch the `WalletSystem.exe` immediately in your terminal.
   * 
                                    ##  OR
     There is also simple way to Run with run.bat go to folder where is this project if you have folder on
     desktop open folder and double click it will show terminal and run the program automatically...

### Method 2: Manual Terminal Compilation

If you are on a different operating system (Linux/Mac) or prefer using the terminal directly, follow these steps:

1. Open your terminal (or VS Code integrated terminal) and navigate to the project directory.
2. Run the following compile command to link all files:

```g++ main.cpp FileManager.cpp Transaction.cpp User.cpp Wallet.cpp -o WalletSystem```

after that also paste this in terminal.


```.\WalletSystem.exe```
