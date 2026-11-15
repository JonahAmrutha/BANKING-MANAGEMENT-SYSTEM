#ifndef DEPOSIT_MANAGER_H
#define DEPOSIT_MANAGER_H

#include "Account.h"
#include "Transaction.h"
#include <iostream>

class DepositManager : public Account
{
public:

    DepositManager(const std::string& custId, double openingBalance)
        : Account(custId, openingBalance)
    {
    }

    std::string getAccountType() const override
    {
        return "Deposit Account";
    }

    void depositMoney(double amount,
                      const std::string& transactionId = "D001")
    {
        if (amount <= 0)
        {
            std::cout << "Invalid deposit amount!" << std::endl;
            return;
        }

        setBalance(getBalance() + amount);

        Transaction t(transactionId, getAccountNumber(),
                      "Deposit", amount);

        std::cout << "\nDeposit successful!" << std::endl;
        t.displayTransaction();

        std::cout << "Updated Balance: "
                  << getBalance() << std::endl;
    }
};

#endif