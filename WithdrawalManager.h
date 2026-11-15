#ifndef WITHDRAWAL_MANAGER_H
#define WITHDRAWAL_MANAGER_H

#include "Account.h"
#include "TransactionValidator.h"
#include <iostream>

class WithdrawalManager : public Account {
private:
    double minimumBalance;

public:

    WithdrawalManager(const std::string& custId,
                      double openingBalance,
                      double minBalance = 0.0)
        : Account(custId, openingBalance),
          minimumBalance(minBalance) {
    }

    std::string getAccountType() const override {
        return "Withdrawal Account";
    }

    bool withdrawMoney(double amount) {

        if (!TransactionValidator::isValidAmount(amount)) {
            std::cout << "Invalid withdrawal amount!\n";
            return false;
        }

        if (!TransactionValidator::canWithdraw(
                getBalance(), amount, minimumBalance)) {
            std::cout << "Insufficient balance!\n";
            return false;
        }

        setBalance(getBalance() - amount);

        std::cout << "Withdrawal successful!\n";
        std::cout << "Remaining balance: " << getBalance() << '\n';

        return true;
    }
};

#endif