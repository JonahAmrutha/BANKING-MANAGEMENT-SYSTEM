#ifndef TRANSACTIONS_H
#define TRANSACTIONS_H

#include <iostream>
using namespace std;

// Abstract Base Class
class Transaction
{
protected:
    int transactionId;
    double amount;

public:
    Transaction(int id, double amt)
    {
        transactionId = id;
        amount = amt;
    }

    virtual void display() const = 0;

    virtual ~Transaction() {}
};

// Deposit Class
class Deposit : public Transaction
{
public:
    Deposit(int id, double amt)
        : Transaction(id, amt) {}

    void display() const override;
};

// Withdrawal Class
class Withdrawal : public Transaction
{
public:
    Withdrawal(int id, double amt)
        : Transaction(id, amt) {}

    void display() const override;
};

// Transfer Class
class Transfer : public Transaction
{
private:
    int receiverAccount;

public:
    Transfer(int id, double amt, int receiver)
        : Transaction(id, amt)
    {
        receiverAccount = receiver;
    }

    void display() const override;
};

#endif