#pragma once
#include "User.h"
#include "Wallet.h"
#include <vector>
#include <string>

using namespace std;

class FileManager {
public:
    // Save functions [cite: 106, 108]
    static void saveUsers(const vector<User>& users);
    static void saveWallets(const vector<Wallet>& wallets);
static void logTransaction(string tID, string type, double amount, string sender, string receiver, string date);
    // Load functions [cite: 107, 109]
    static vector<User> loadUsers();
    static vector<Wallet> loadWallets();
};