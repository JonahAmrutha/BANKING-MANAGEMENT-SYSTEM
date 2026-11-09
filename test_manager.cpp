#include <iostream>
#include "AccountManager.h"

int main() {
    AccountManager m;
    std::string id = m.registerCustomer("Asha", "9876543210", "Vijayawada");
    Account* a = m.createAccount(id, "Savings", 5000);
    std::cout << a->getAccountNumber() << " " << a->getAccountType() << "\n";
    std::cout << (m.findAccount("ACC9999") == nullptr ? "not found\n" : "found\n");
    return 0;
}