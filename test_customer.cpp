#include <iostream>
#include "AccountManager.h"

int main() {
    AccountManager m;
    std::string id = m.registerCustomer("Asha", "9876543210", "Vijayawada");
    m.createAccount(id, "Savings", 5000);
    m.createAccount(id, "Current", 10000);

    m.viewCustomer(id);
    m.updateCustomer(id, "", "9123456780", "Guntur");
    std::cout << "--- after update ---\n";
    m.viewCustomer(id);
    m.viewCustomer("C99");
    return 0;
}