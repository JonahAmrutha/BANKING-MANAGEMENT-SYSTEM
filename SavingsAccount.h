#pragma once
#include "Account.h"

class SavingsAccount : public Account {
public:
    SavingsAccount(const std::string& custId, double openingBalance)
        : Account(custId, openingBalance) {}

    std::string getAccountType() const override { return "Savings"; }
};