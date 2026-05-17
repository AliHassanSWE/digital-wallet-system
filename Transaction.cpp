#include <iostream>
#include <string>
#include "Transaction.h"

using namespace std;

Transaction::Transaction(string tID, string tType, double amt, string sID, string rID, string d)
{
    transactionID = tID;
    type = tType;
    amount = amt;
    senderID = sID;
    receiverID = rID;
    date = d;
}

void Transaction::displayTransaction() const
{
    cout << "[" << date << "] " << type << " | Rs. " << amount
         << " | Sender: " << senderID << " | Receiver: " << receiverID << "\n";
}

string Transaction::toFileString() const
{
    return transactionID + " " + type + " " + to_string(amount) + " " + senderID + " " + receiverID + " " + date;
}