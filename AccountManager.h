#pragma once
#include <map>
#include <memory>
#include <string>
#include "Customer.h"
#include "SavingsAccount.h"
#include "CurrentAccount.h"

class AccountManager {
private:
    std::map<std::string, Customer> customers;
    std::map<std::string, std::unique_ptr<Account>> accounts;
    int customerCounter = 0;

public:
    std::string registerCustomer(const std::string& name,
                                 const std::string& phone,
                                 const std::string& address) {
        std::string id = "C" + std::to_string(++customerCounter);
        customers.emplace(id, Customer(id, name, phone, address));
        return id;
    }

    Customer* findCustomer(const std::string& id) {
        auto it = customers.find(id);
        return it == customers.end() ? nullptr : &it->second;
    }

    Account* createAccount(const std::string& customerId,
                           const std::string& type, double openingBalance) {
        if (!findCustomer(customerId)) return nullptr;
        std::unique_ptr<Account> acc;
        if (type == "Savings") acc = std::make_unique<SavingsAccount>(customerId, openingBalance);
        else if (type == "Current") acc = std::make_unique<CurrentAccount>(customerId, openingBalance);
        else return nullptr;
        Account* raw = acc.get();
        accounts[raw->getAccountNumber()] = std::move(acc);
        return raw;
    }

    Account* findAccount(const std::string& accNo) {
        auto it = accounts.find(accNo);
        return it == accounts.end() ? nullptr : it->second.get();
    }
};