#include <iostream>
#include <string>
#include "AccountManager.h"

namespace {

const std::string ADMIN_USER = "admin";
const std::string ADMIN_PASS = "admin123";

// ---------- input helpers ----------

// Reads one line. Returns false when input has ended (EOF).
bool readLine(const std::string& prompt, std::string& out) {
    std::cout << prompt;
    return static_cast<bool>(std::getline(std::cin, out));
}

// Returns the menu choice, -1 for invalid input, 0 when input has ended
// (so every menu logs out / exits instead of looping forever).
int readChoice(const std::string& prompt) {
    std::string line;
    if (!readLine(prompt, line)) return 0;
    try {
        std::size_t pos = 0;
        int value = std::stoi(line, &pos);
        if (pos != line.size()) return -1;
        return value;
    } catch (const std::exception&) {
        return -1;
    }
}

// Reads a text field. Empty input is allowed (callers decide what that means).
std::string readText(const std::string& prompt) {
    std::string line;
    if (!readLine(prompt, line)) return "";
    return line;
}

double readAmount(const std::string& prompt) {
    std::string line;
    readLine(prompt, line);
    try {
        std::size_t pos = 0;
        double value = std::stod(line, &pos);
        if (pos != line.size()) throw BankException("Please enter a valid number");
        return value;
    } catch (const BankException&) {
        throw;
    } catch (const std::exception&) {
        throw BankException("Please enter a valid number");
    }
}

void comingSoon(const std::string& feature) {
    std::cout << feature << " is not available yet (waiting for another module).\n";
}

// ---------- shared actions ----------

void printAccount(const Account& acc, const Customer& owner) {
    std::cout << "Account Number: " << acc.getAccountNumber() << "\n"
              << "Type: " << acc.getAccountType() << "\n"
              << "Balance: " << acc.getBalance() << "\n"
              << "Owner: " << owner.getName() << " (" << owner.getCustomerId() << ")\n";
}

void updateCustomerFlow(AccountManager& manager, const std::string& customerId) {
    std::cout << "Leave a field blank to keep its current value.\n";
    std::string name = readText("New name: ");
    std::string phone = readText("New phone: ");
    std::string address = readText("New address: ");
    if (manager.updateCustomer(customerId, name, phone, address)) {
        std::cout << "Customer details updated.\n";
    } else {
        std::cout << "Customer not found.\n";
    }
}

// ---------- admin ----------

void registerCustomerFlow(AccountManager& manager) {
    std::string name = readText("Name: ");
    std::string phone = readText("Phone (10 digits): ");
    std::string address = readText("Address: ");
    std::string id = manager.registerCustomer(name, phone, address);
    std::cout << "Customer registered. Customer ID: " << id << "\n";
}

void createAccountFlow(AccountManager& manager) {
    std::string customerId = readText("Customer ID: ");
    if (!manager.findCustomer(customerId)) {
        std::cout << "Customer not found.\n";
        return;
    }
    int typeChoice = readChoice("Account type (1 = Savings, 2 = Current): ");
    std::string type;
    if (typeChoice == 1) type = "Savings";
    else if (typeChoice == 2) type = "Current";
    else {
        std::cout << "Invalid account type.\n";
        return;
    }
    double opening = readAmount("Opening balance: ");
    Account* acc = manager.createAccount(customerId, type, opening);
    if (acc) {
        std::cout << type << " account created. Account Number: "
                  << acc->getAccountNumber() << "\n";
    } else {
        std::cout << "Could not create account.\n";
    }
}

void searchAccountFlow(AccountManager& manager) {
    std::string accNo = readText("Account number: ");
    Account* acc = manager.findAccount(accNo);
    if (!acc) {
        std::cout << "Account not found.\n";
        return;
    }
    Customer* owner = manager.findCustomer(acc->getCustomerId());
    if (owner) printAccount(*acc, *owner);
}

void adminMenu(AccountManager& manager) {
    while (true) {
        std::cout << "\n===== ADMIN MENU =====\n"
                  << "1. Register customer\n"
                  << "2. Create account\n"
                  << "3. View customer details\n"
                  << "4. Update customer details\n"
                  << "5. Search account\n"
                  << "6. Deposit\n"
                  << "7. Withdraw\n"
                  << "8. Transfer money\n"
                  << "9. Transaction history\n"
                  << "0. Logout\n";
        int choice = readChoice("Choice: ");
        try {
            switch (choice) {
                case 1: registerCustomerFlow(manager); break;
                case 2: createAccountFlow(manager); break;
                case 3: manager.viewCustomer(readText("Customer ID: ")); break;
                case 4: updateCustomerFlow(manager, readText("Customer ID: ")); break;
                case 5: searchAccountFlow(manager); break;
                case 6: comingSoon("Deposit"); break;
                case 7: comingSoon("Withdraw"); break;
                case 8: comingSoon("Transfer"); break;
                case 9: comingSoon("Transaction history"); break;
                case 0: return;
                default: std::cout << "Invalid choice.\n";
            }
        } catch (const BankException& e) {
            std::cout << "Error: " << e.what() << "\n";
        }
    }
}

// ---------- customer ----------

void customerSearchFlow(AccountManager& manager, const std::string& customerId) {
    std::string accNo = readText("Account number: ");
    Account* acc = manager.findAccount(accNo);
    // Customers may only see their own accounts.
    if (!acc || acc->getCustomerId() != customerId) {
        std::cout << "Account not found.\n";
        return;
    }
    Customer* owner = manager.findCustomer(customerId);
    if (owner) printAccount(*acc, *owner);
}

void customerMenu(AccountManager& manager, const std::string& customerId) {
    while (true) {
        std::cout << "\n===== CUSTOMER MENU =====\n"
                  << "1. View my details and accounts\n"
                  << "2. Update my details\n"
                  << "3. Search my account\n"
                  << "4. Deposit\n"
                  << "5. Withdraw\n"
                  << "6. Transfer money\n"
                  << "7. Transaction history\n"
                  << "0. Logout\n";
        int choice = readChoice("Choice: ");
        try {
            switch (choice) {
                case 1: manager.viewCustomer(customerId); break;
                case 2: updateCustomerFlow(manager, customerId); break;
                case 3: customerSearchFlow(manager, customerId); break;
                case 4: comingSoon("Deposit"); break;
                case 5: comingSoon("Withdraw"); break;
                case 6: comingSoon("Transfer"); break;
                case 7: comingSoon("Transaction history"); break;
                case 0: return;
                default: std::cout << "Invalid choice.\n";
            }
        } catch (const BankException& e) {
            std::cout << "Error: " << e.what() << "\n";
        }
    }
}

// ---------- login ----------

void adminLogin(AccountManager& manager) {
    std::string user = readText("Admin username: ");
    std::string pass = readText("Admin password: ");
    if (user == ADMIN_USER && pass == ADMIN_PASS) {
        adminMenu(manager);
    } else {
        std::cout << "Invalid admin credentials.\n";
    }
}

// A customer logs in with their Customer ID and their registered phone number.
void customerLogin(AccountManager& manager) {
    std::string id = readText("Customer ID: ");
    std::string phone = readText("Phone number: ");
    Customer* c = manager.findCustomer(id);
    if (c && c->getPhone() == phone) {
        std::cout << "Welcome, " << c->getName() << "!\n";
        customerMenu(manager, id);
    } else {
        std::cout << "Invalid customer ID or phone number.\n";
    }
}

}  // namespace

int main() {
    AccountManager manager;

    while (true) {
        std::cout << "\n===== BANKING MANAGEMENT SYSTEM =====\n"
                  << "1. Admin login\n"
                  << "2. Customer login\n"
                  << "0. Exit\n";
        int choice = readChoice("Choice: ");
        switch (choice) {
            case 1: adminLogin(manager); break;
            case 2: customerLogin(manager); break;
            case 0: std::cout << "Goodbye.\n"; return 0;
            default: std::cout << "Invalid choice.\n";
        }
    }
}
