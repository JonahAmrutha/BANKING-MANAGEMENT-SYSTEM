#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <iostream>
#include <string>
using namespace std;

class Transaction
{
private:
    string transactionId;
    string accountNumber;
    string transactionType;
    double amount;

public:

    // Constructor
    Transaction(string id, string accNo, string type, double amt)
    {
        transactionId = id;
        accountNumber = accNo;
        transactionType = type;
        amount = amt;
    }

    // Getter functions
    string getTransactionId()
    {
        return transactionId;
    }

    string getAccountNumber()
    {
        return accountNumber;
    }

    string getTransactionType()
    {
        return transactionType;
    }

    double getAmount()
    {
        return amount;
    }

    // Display transaction details
    void displayTransaction()
    {
        cout << "\nTransaction ID: " << transactionId;
        cout << "\nAccount Number: " << accountNumber;
        cout << "\nTransaction Type: " << transactionType;
        cout << "\nAmount: " << amount << endl;
    }
};

#endif