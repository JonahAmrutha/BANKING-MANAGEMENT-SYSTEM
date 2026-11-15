#pragma once
#include <string>
#include <vector>
#include "BankException.h"
#include "TransactionRecord.h"

class AccountManager;

class Account {
    friend class AccountManager;  // only the manager may move money between accounts

private:
    std::string accountNumber;
    std::string customerId;
    double balance;
    std::vector<TransactionRecord> history;

    inline static int txCounter = 0;

    static std::string generateAccountNumber() {
        static int counter = 1000;
        return "ACC" + std::to_string(counter++);
    }

    void record(const std::string& type, double amount,
                const std::string& other = "") {
        std::string id = "T" + std::to_string(++txCounter);
        history.emplace_back(id, type, accountNumber, other, amount, balance);
    }

    // Used by AccountManager::transfer after it has validated both accounts.
    void transferOut(double amount, const std::string& toAccount) {
        checkWithdraw(amount);
        balance -= amount;
        record("Transfer Out", amount, toAccount);
    }

    void transferIn(double amount, const std::string& fromAccount) {
        if (!(amount > 0)) throw BankException("Transfer amount must be greater than zero");
        balance += amount;
        record("Transfer In", amount, fromAccount);
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

    std::string getAccountNumber() const { return accountNumber; }
    std::string getCustomerId() const { return customerId; }
    double getBalance() const { return balance; }
    const std::vector<TransactionRecord>& getHistory() const { return history; }

    virtual std::string getAccountType() const = 0;

    // Account types override these (polymorphism).
    virtual double getMinimumBalance() const { return 0.0; }
    virtual double getInterestRate() const { return 0.0; }  // percent per year

    // Throws BankException if the amount is invalid or breaks the minimum balance.
    void checkWithdraw(double amount) const {
        if (!(amount > 0)) throw BankException("Withdrawal amount must be greater than zero");
        if (balance - amount < getMinimumBalance()) {
            throw BankException("Insufficient balance (minimum balance rule)");
        }
    }

    void deposit(double amount) {
        if (!(amount > 0)) throw BankException("Deposit amount must be greater than zero");
        balance += amount;
        record("Deposit", amount);
    }

    void withdraw(double amount) {
        checkWithdraw(amount);
        balance -= amount;
        record("Withdrawal", amount);
    }

    // Simple interest for the given number of years.
    double calculateInterest(double years) const {
        if (!(years >= 0)) throw BankException("Years cannot be negative");
        return balance * getInterestRate() * years / 100.0;
    }
};
