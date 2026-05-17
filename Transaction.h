#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>

using namespace std;

class Transaction
{
private:
    string transactionID;
    string type;
    double amount;
    string senderID;
    string receiverID;
    string date;

public:
    Transaction(string tID, string tType, double amt,
                string sID, string rID, string d);
    void displayTransaction() const;
    string toFileString() const;
};

#endif