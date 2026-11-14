#include <iostream>
#include "AccountManager.h"

int main() {
    AccountManager m;

    try {
        m.registerCustomer("", "9876543210", "Vijayawada");
    } catch (const BankException& e) {
        std::cout << "Rejected: " << e.what() << "\n";
    }

    try {
        m.registerCustomer("Asha", "12345", "Vijayawada");
    } catch (const BankException& e) {
        std::cout << "Rejected: " << e.what() << "\n";
    }

    try {
        m.registerCustomer("Asha", "98765abcde", "Vijayawada");
    } catch (const BankException& e) {
        std::cout << "Rejected: " << e.what() << "\n";
    }

    std::string id = m.registerCustomer("Asha", "9876543210", "Vijayawada");
    std::cout << "Registered: " << id << "\n";

    try {
        m.createAccount(id, "Savings", -100);
    } catch (const BankException& e) {
        std::cout << "Rejected: " << e.what() << "\n";
    }

    try {
        m.updateCustomer(id, "Priya", "bad", "");
    } catch (const BankException& e) {
        std::cout << "Rejected: " << e.what() << "\n";
    }
    std::cout << "Name after failed update: " << m.findCustomer(id)->getName() << "\n";

    Account* a = m.createAccount(id, "Savings", 0);
    std::cout << "Zero balance account created: " << (a != nullptr ? "yes" : "no") << "\n";
    std::cout << "Unknown type returns null: " << (m.createAccount(id, "Gold", 100) == nullptr ? "yes" : "no") << "\n";
    return 0;
}