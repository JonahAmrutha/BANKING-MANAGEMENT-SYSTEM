#include <iostream>
#include "Deposit.h"
#include "Withdrawal.h"

using namespace std;

int main()
{
    cout << "===== DEPOSIT TEST =====" << endl;

    Deposit d1("C001", 1000);

    d1.depositMoney(500, "T001");

    cout << "\n===== WITHDRAWAL TEST =====" << endl;

    Withdrawal w1("C001", 1000);

    w1.withdrawMoney(200, "T002");

    return 0;
}