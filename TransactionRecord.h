#pragma once
#include <string>

// One entry in an account's transaction history.
class TransactionRecord {
private:
    std::string id;
    std::string type;           // Deposit, Withdrawal, Transfer Out, Transfer In
    std::string accountNumber;  // account this record belongs to
    std::string otherAccount;   // other side of a transfer (empty otherwise)
    double amount;
    double balanceAfter;

public:
    TransactionRecord(const std::string& id, const std::string& type,
                      const std::string& accountNumber,
                      const std::string& otherAccount,
                      double amount, double balanceAfter)
        : id(id), type(type), accountNumber(accountNumber),
          otherAccount(otherAccount), amount(amount), balanceAfter(balanceAfter) {}

    std::string getId() const { return id; }
    std::string getType() const { return type; }
    std::string getAccountNumber() const { return accountNumber; }
    std::string getOtherAccount() const { return otherAccount; }
    double getAmount() const { return amount; }
    double getBalanceAfter() const { return balanceAfter; }
};
