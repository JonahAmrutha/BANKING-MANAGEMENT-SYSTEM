#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <iostream>
#include <string>

class Account {
private:
    std::string accountNumber;
    std::string customerId;
    double balance;

    static std::string generateAccountNumber() {
        static int counter = 1000;
        return "ACC" + std::to_string(counter++);
    }

protected:
    void setBalance(double b) {
        balance = b;
    }

public:
    Account(const std::string& custId, double openingBalance)
        : accountNumber(generateAccountNumber()),
          customerId(custId),
          balance(openingBalance) {
    }

    virtual ~Account() {}

    std::string getAccountNumber() const {
        return accountNumber;
    }

    std::string getCustomerId() const {
        return customerId;
    }

    double getBalance() const {
        return balance;
    }

    virtual std::string getAccountType() const = 0;
};

#endif