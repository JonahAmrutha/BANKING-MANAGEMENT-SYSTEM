#include "transactions.h"

int main()
{
    Deposit d1(101, 5000);
    Withdrawal w1(102, 2000);
    Transfer t1(103, 3000, 2002);

    // Polymorphism
    Transaction* transactions[3];

    transactions[0] = &d1;
    transactions[1] = &w1;
    transactions[2] = &t1;

    cout << "BANKING MANAGEMENT SYSTEM\n";
    cout << "TRANSACTION DETAILS\n";

    for (int i = 0; i < 3; i++)
    {
        transactions[i]->display();
    }

    return 0;
}