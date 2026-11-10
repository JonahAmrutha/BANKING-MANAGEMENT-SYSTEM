#include "transactions.h"

// Deposit Transaction
void Deposit::display() const
{
    cout << "\nTransaction ID: " << transactionId;
    cout << "\nTransaction Type: Deposit";
    cout << "\nAmount: Rs. " << amount << endl;
}

// Withdrawal Transaction
void Withdrawal::display() const
{
    cout << "\nTransaction ID: " << transactionId;
    cout << "\nTransaction Type: Withdrawal";
    cout << "\nAmount: Rs. " << amount << endl;
}

// Transfer Transaction
void Transfer::display() const
{
    cout << "\nTransaction ID: " << transactionId;
    cout << "\nTransaction Type: Transfer";
    cout << "\nAmount: Rs. " << amount;
    cout << "\nReceiver Account: " << receiverAccount << endl;
}