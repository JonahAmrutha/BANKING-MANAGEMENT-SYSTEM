#include <iostream>
#include "Customer.h"
#include "SavingsAccount.h"
#include "CurrentAccount.h"

int main() {
    Customer c("C1", "Asha", "9876543210", "Vijayawada");
    SavingsAccount s(c.getCustomerId(), 5000);
    CurrentAccount cur(c.getCustomerId(), 10000);

    std::cout << s.getAccountNumber() << " " << s.getAccountType() << " " << s.getBalance() << "\n";
    std::cout << cur.getAccountNumber() << " " << cur.getAccountType() << " " << cur.getBalance() << "\n";
    return 0;
}