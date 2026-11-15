#pragma once
#include "Account.h"

class CurrentAccount : public Account {
public:
    CurrentAccount(const std::string& custId, double openingBalance)
        : Account(custId, openingBalance) {}

    std::string getAccountType() const override { return "Current"; }
    double getMinimumBalance() const override { return 0.0; }
    double getInterestRate() const override { return 0.0; }
};
