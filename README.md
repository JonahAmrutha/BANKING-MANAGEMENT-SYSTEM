# Banking Management System

A C++ console application that demonstrates Object-Oriented Programming concepts.

## Team
| Member | Module | OOP concepts |
|---|---|---|
| Member 1 (Trilok) | Customer and account management | Encapsulation, Abstraction |
| Member 2 (Amrutha) | Deposit and withdrawal | Inheritance, Encapsulation |
| Member 3 (Bhavitha) | Transfer and transaction history | Polymorphism, Abstraction |
| Member 4 (Nithin) | Login, menu and integration | All modules |

## How to compile and run
```
g++ -std=c++17 main.cpp -o main
./main
```
On Windows PowerShell use `.\main`.

## Login details
- Admin: username `admin`, password `admin123`
- Customer: Customer ID and registered phone number

## Features
- Register customers and create Savings or Current accounts
- View, update and search customer and account details
- Deposit and withdraw money (TODO: confirm after integration)
- Transfer money and view transaction history (TODO: confirm after integration)
- Input validation with exception handling (`BankException`)

## OOP concepts used
| Concept | Where |
|---|---|
| Encapsulation | Private fields in `Customer` and `Account`. `setBalance` is protected. |
| Abstraction | `Account` is abstract (pure virtual `getAccountType()`). |
| Inheritance | `SavingsAccount` and `CurrentAccount` extend `Account`. |
| Polymorphism | Accounts are stored as `Account*`, so one container holds both types. |
| Exception handling | `BankException` for invalid input and invalid transactions. |

## Project files
| File | Purpose |
|---|---|
| `main.cpp` | Login and menus |
| `AccountManager.h` | Customer and account management |
| `Customer.h`, `Account.h`, `SavingsAccount.h`, `CurrentAccount.h` | Customer and account classes |
| `BankException.h` | Custom exception |
| TODO | Member 2 and Member 3 files |

Detailed notes on Member 1's module are in `README_MEMBER1.md`. The test cases are in `TEST_PLAN.md`.

## Limitations
- Data is stored in memory only and is lost when the program exits.
