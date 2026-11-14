#include <iostream>
#include "DepositManager.h"
#include "WithdrawalManager.h"

int main() {

    std::cout << "===== MEMBER 2 TESTING =====\n\n";

    // Deposit testing
    DepositManager depositAccount("C101", 5000);

    std::cout << "--- DEPOSIT TEST ---\n";
    depositAccount.depositMoney(1000);
    depositAccount.depositMoney(-200);

    // Withdrawal testing
    WithdrawalManager withdrawalAccount("C102", 5000, 1000);

    std::cout << "\n--- WITHDRAWAL TEST ---\n";
    withdrawalAccount.withdrawMoney(2000);
    withdrawalAccount.withdrawMoney(4500);
    withdrawalAccount.withdrawMoney(-100);

    std::cout << "\n===== TESTING COMPLETED =====\n";

    return 0;
}