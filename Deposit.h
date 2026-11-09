#ifndef DEPOSIT_H
#define DEPOSIT_H

#include <iostream>
#include <string>
#include "Account.h"
#include "Transaction.h"

class Deposit : public Account
{
public:

    // Constructor
    Deposit(const std::string& custId, double openingBalance)
        : Account(custId, openingBalance)
    {
    }

    // Deposit function
    bool depositMoney(double amount, const std::string& transactionId)
    {
        if (amount <= 0)
        {
            std::cout << "Invalid deposit amount!" << std::endl;
            return false;
        }

        setBalance(getBalance() + amount);

        Transaction t(transactionId, getAccountNumber(),
                       "Deposit", amount);

        std::cout << "\nDeposit successful!" << std::endl;
        t.displayTransaction();

        std::cout << "Updated Balance: "
                  << getBalance() << std::endl;

        return true;
    }
};

#endif