#pragma once
#include <string>

class Account {
private:
    inline static int counter = 1000;
    std::string accountNumber;
    std::string customerId;
    double balance;

protected:
    void setBalance(double b) { balance = b; }

public:
    Account(const std::string& custId, double openingBalance)
        : accountNumber("ACC" + std::to_string(++counter)),
          customerId(custId), balance(openingBalance) {}

    virtual ~Account() {}

    std::string getAccountNumber() const { return accountNumber; }
    std::string getCustomerId() const { return customerId; }
    double getBalance() const { return balance; }

    virtual std::string getAccountType() const = 0;
};