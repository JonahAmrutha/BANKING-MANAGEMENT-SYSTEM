#pragma once
#include "Account.h"

class CurrentAccount : public Account {
public:
    CurrentAccount(const std::string& custId, double openingBalance)
        : Account(custId, openingBalance) {}

    std::string getAccountType() const override { return "Current"; }
};