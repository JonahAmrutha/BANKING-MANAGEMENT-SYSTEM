#pragma once
#include <string>

class Customer {
private:
    std::string customerId;
    std::string name;
    std::string phone;
    std::string address;

public:
    Customer(const std::string& id, const std::string& name,
             const std::string& phone, const std::string& address)
        : customerId(id), name(name), phone(phone), address(address) {}

    std::string getCustomerId() const { return customerId; }
    std::string getName() const { return name; }
    std::string getPhone() const { return phone; }
    std::string getAddress() const { return address; }

    void setName(const std::string& n) { name = n; }
    void setPhone(const std::string& p) { phone = p; }
    void setAddress(const std::string& a) { address = a; }
};