#pragma once
#include <cctype>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <utility>
#include "BankException.h"
#include "Customer.h"
#include "SavingsAccount.h"
#include "CurrentAccount.h"

class AccountManager {
private:
    std::map<std::string, Customer> customers;
    std::map<std::string, std::unique_ptr<Account>> accounts;
    int customerCounter = 0;

    static bool isBlank(const std::string& s) {
        for (unsigned char ch : s) {
            if (!std::isspace(ch)) return false;
        }
        return true;
    }

    static bool isValidPhone(const std::string& p) {
        if (p.size() != 10) return false;
        for (unsigned char ch : p) {
            if (!std::isdigit(ch)) return false;
        }
        return true;
    }

    static void validateName(const std::string& name) {
        if (isBlank(name)) throw BankException("Name cannot be empty");
    }

    static void validatePhone(const std::string& phone) {
        if (!isValidPhone(phone)) throw BankException("Phone must be exactly 10 digits");
    }

    static void validateAddress(const std::string& address) {
        if (isBlank(address)) throw BankException("Address cannot be empty");
    }

public:
    // Throws BankException if name, phone or address is invalid.
    std::string registerCustomer(const std::string& name,
                                 const std::string& phone,
                                 const std::string& address) {
        validateName(name);
        validatePhone(phone);
        validateAddress(address);
        std::string id = "C" + std::to_string(++customerCounter);
        customers.emplace(id, Customer(id, name, phone, address));
        return id;
    }

    // Returns nullptr if the customer does not exist.
    Customer* findCustomer(const std::string& id) {
        auto it = customers.find(id);
        return it == customers.end() ? nullptr : &it->second;
    }

    // Returns nullptr if the customer or type is unknown.
    // Throws BankException if the opening balance is negative.
    Account* createAccount(const std::string& customerId,
                           const std::string& type, double openingBalance) {
        if (!(openingBalance >= 0)) throw BankException("Opening balance cannot be negative");
        if (!findCustomer(customerId)) return nullptr;
        std::unique_ptr<Account> acc;
        if (type == "Savings") acc = std::make_unique<SavingsAccount>(customerId, openingBalance);
        else if (type == "Current") acc = std::make_unique<CurrentAccount>(customerId, openingBalance);
        else return nullptr;
        Account* raw = acc.get();
        accounts[raw->getAccountNumber()] = std::move(acc);
        return raw;
    }

    // Returns nullptr if the account does not exist.
    Account* findAccount(const std::string& accNo) {
        auto it = accounts.find(accNo);
        return it == accounts.end() ? nullptr : it->second.get();
    }

    bool viewCustomer(const std::string& id) {
        Customer* c = findCustomer(id);
        if (!c) {
            std::cout << "Customer not found\n";
            return false;
        }
        std::cout << "ID: " << c->getCustomerId() << "\n"
                  << "Name: " << c->getName() << "\n"
                  << "Phone: " << c->getPhone() << "\n"
                  << "Address: " << c->getAddress() << "\n"
                  << "Accounts:\n";
        for (const auto& entry : accounts) {
            const Account* acc = entry.second.get();
            if (acc->getCustomerId() == id) {
                std::cout << "  " << acc->getAccountNumber() << " "
                          << acc->getAccountType() << " "
                          << acc->getBalance() << "\n";
            }
        }
        return true;
    }

    // Empty string = leave that field unchanged.
    // Returns false if the customer does not exist.
    // Throws BankException if a non-empty value is invalid; nothing is changed in that case.
    bool updateCustomer(const std::string& id, const std::string& name,
                        const std::string& phone, const std::string& address) {
        Customer* c = findCustomer(id);
        if (!c) return false;
        if (!name.empty()) validateName(name);
        if (!phone.empty()) validatePhone(phone);
        if (!address.empty()) validateAddress(address);
        if (!name.empty()) c->setName(name);
        if (!phone.empty()) c->setPhone(phone);
        if (!address.empty()) c->setAddress(address);
        return true;
    }
};