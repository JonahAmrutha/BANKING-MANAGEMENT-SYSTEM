#pragma once

#include <iostream>
#include <string>

class Account {
private:

    std::string accountNumber;
    std::string customerId;
    double balance;

    // Generate unique account numbers
    static std::string generateAccountNumber() {
        static int counter = 1000;

        return "ACC" + std::to_string(counter++);
    }

protected:

    void setBalance(double b) {
        balance = b;
    }

public:

    // Constructor
    Account(const std::string& custId, double openingBalance)
        : accountNumber(generateAccountNumber()),
          customerId(custId),
          balance(openingBalance) {
    }

    // Virtual destructor
    virtual ~Account() {
    }

    // Get account number
    std::string getAccountNumber() const {
        return accountNumber;
    }

    // Get customer ID
    std::string getCustomerId() const {
        return customerId;
    }

    // Get balance
    double getBalance() const {
        return balance;
    }

    // Pure virtual function
    virtual std::string getAccountType() const = 0;
};
