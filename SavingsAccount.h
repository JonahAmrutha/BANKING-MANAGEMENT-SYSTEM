#pragma once
#include "Account.h"

class SavingsAccount : public Account {
public:
    SavingsAccount(const std::string& custId, double openingBalance)
        : Account(custId, openingBalance) {}

    std::string getAccountType() const override { return "Savings"; }
    double getMinimumBalance() const override { return 500.0; }
    double getInterestRate() const override { return 4.0; }
};
