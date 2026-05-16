#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>

class Transaction {
private:
    std::string transactionID;
    std::string type;
    double amount;
    std::string senderID;
    std::string receiverID;
    std::string date;

public:
    Transaction(std::string tID, std::string tType, double amt, 
                std::string sID, std::string rID, std::string d);
    void displayTransaction() const;
    std::string toFileString() const;
};

#endif