#ifndef DEPOSIT_MANAGER_H
#define DEPOSIT_MANAGER_H

#include "Account.h"
#include "Transaction.h"
#include <iostream>
using namespace std;

class DepositManager {
public:

    void depositMoney(Account& account, double amount) {

        if (amount <= 0) {
            cout << "Invalid deposit amount!" << endl;
            return;
        }

        double newBalance = account.getBalance() + amount;

        account.setBalance(newBalance);

        cout << "Deposit Successful!" << endl;
        cout << "Updated Balance: "
             << account.getBalance() << endl;
    }
};

#endif