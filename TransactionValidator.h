#ifndef TRANSACTION_VALIDATOR_H
#define TRANSACTION_VALIDATOR_H

class TransactionValidator {
public:

    static bool isValidAmount(double amount) {
        return amount > 0;
    }

    static bool canWithdraw(double balance,
                            double amount,
                            double minimumBalance) {

        return amount > 0 &&
               minimumBalance >= 0 &&
               balance >= amount &&
               (balance - amount) >= minimumBalance;
    }
};

#endif