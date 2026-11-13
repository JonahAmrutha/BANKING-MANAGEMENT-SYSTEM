
#include <iostream>
#include <vector>
#include <map>
#include <memory>
#include <string>
#include <iomanip>
#include <ctime>
#include <limits>

using namespace std;

// ==========================================
// ABSTRACT BASE CLASS
// ==========================================

class Transaction
{
protected:
    int transactionId;
    int accountNumber;
    double amount;
    string dateTime;

public:

    Transaction(int id, int acc, double amt)
    {
        transactionId = id;
        accountNumber = acc;
        amount = amt;

        time_t now = time(nullptr);
        dateTime = ctime(&now);

        if (!dateTime.empty() && dateTime.back() == '\n')
        {
            dateTime.pop_back();
        }
    }

    // Getter functions
    int getAccountNumber() const
    {
        return accountNumber;
    }

    double getAmount() const
    {
        return amount;
    }

    // Pure virtual function
    virtual void display() const = 0;

    virtual ~Transaction() {}
};

// ==========================================
// DEPOSIT CLASS
// ==========================================

class Deposit : public Transaction
{
public:

    Deposit(int id, int acc, double amt)
        : Transaction(id, acc, amt) {}

    void display() const override
    {
        cout << "\nTransaction ID: " << transactionId;
        cout << "\nTransaction Type: Deposit";
        cout << "\nAccount Number: " << accountNumber;
        cout << "\nAmount: Rs. " << amount;
        cout << "\nDate: " << dateTime << endl;
    }
};

// ==========================================
// WITHDRAWAL CLASS
// ==========================================

class Withdrawal : public Transaction
{
public:

    Withdrawal(int id, int acc, double amt)
        : Transaction(id, acc, amt) {}

    void display() const override
    {
        cout << "\nTransaction ID: " << transactionId;
        cout << "\nTransaction Type: Withdrawal";
        cout << "\nAccount Number: " << accountNumber;
        cout << "\nAmount: Rs. " << amount;
        cout << "\nDate: " << dateTime << endl;
    }
};

// ==========================================
// TRANSFER CLASS
// ==========================================

class Transfer : public Transaction
{
private:
    int receiverAccount;

public:

    Transfer(int id, int sender, double amt, int receiver)
        : Transaction(id, sender, amt)
    {
        receiverAccount = receiver;
    }

    int getReceiverAccount() const
    {
        return receiverAccount;
    }

    void display() const override
    {
        cout << "\nTransaction ID: " << transactionId;
        cout << "\nTransaction Type: Money Transfer";
        cout << "\nSender Account: " << accountNumber;
        cout << "\nReceiver Account: " << receiverAccount;
        cout << "\nAmount: Rs. " << amount;
        cout << "\nDate: " << dateTime << endl;
    }
};

// ==========================================
// TRANSACTION MANAGER CLASS
// ==========================================

class TransactionManager
{
private:

    vector<unique_ptr<Transaction>> history;

    map<int, double> balances;

    int nextId;

public:

    TransactionManager()
    {
        nextId = 101;

        // Sample accounts for testing
        balances[1001] = 10000;
        balances[2002] = 5000;
    }

    // ======================================
    // ADD ACCOUNT
    // ======================================

    void addAccount(int acc, double balance)
    {
        if (acc <= 0 || balance < 0 || balances.count(acc))
        {
            cout << "\nInvalid or duplicate account!";
            return;
        }

        balances[acc] = balance;

        cout << "\nAccount added successfully!";
    }

    // ======================================
    // RECORD DEPOSIT
    // ======================================

    void recordDeposit(int acc, double amt)
    {
        if (!balances.count(acc) || amt <= 0)
        {
            cout << "\nInvalid deposit record!";
            return;
        }

        history.push_back(
            make_unique<Deposit>(nextId++, acc, amt)
        );

        cout << "\nDeposit transaction recorded successfully!";
    }

    // ======================================
    // RECORD WITHDRAWAL
    // ======================================

    void recordWithdrawal(int acc, double amt)
    {
        if (!balances.count(acc) || amt <= 0)
        {
            cout << "\nInvalid withdrawal record!";
            return;
        }

        history.push_back(
            make_unique<Withdrawal>(nextId++, acc, amt)
        );

        cout << "\nWithdrawal transaction recorded successfully!";
    }

    // ======================================
    // MONEY TRANSFER
    // ======================================

    void transferMoney(int sender, int receiver, double amt)
    {
        if (!balances.count(sender) || !balances.count(receiver))
        {
            cout << "\nAccount not found!";
            return;
        }

        if (sender == receiver)
        {
            cout << "\nCannot transfer to the same account!";
            return;
        }

        if (amt <= 0)
        {
            cout << "\nInvalid transfer amount!";
            return;
        }

        if (balances[sender] < amt)
        {
            cout << "\nInsufficient balance!";
            return;
        }

        if (amt > numeric_limits<double>::max() - balances[receiver])
        {
            cout << "\nReceiver balance limit exceeded!";
            return;
        }

        // Update balances
        balances[sender] -= amt;
        balances[receiver] += amt;

        // Store transaction
        history.push_back(
            make_unique<Transfer>(
                nextId++, sender, amt, receiver
            )
        );

        cout << "\nMoney transferred successfully!";
    }

    // ======================================
    // TRANSACTION HISTORY
    // ======================================

    void displayHistory() const
    {
        if (history.empty())
        {
            cout << "\nNo transaction history available!";
            return;
        }

        cout << "\n========== TRANSACTION HISTORY ==========\n";

        for (const auto &t : history)
        {
            t->display();
        }
    }

    // ======================================
    // ACCOUNT STATEMENT
    // ======================================

    void generateStatement(int acc) const
    {
        if (!balances.count(acc))
        {
            cout << "\nAccount not found!";
            return;
        }

        double deposits = 0;
        double withdrawals = 0;
        double sent = 0;
        double received = 0;

        for (const auto &t : history)
        {
            if (auto d = dynamic_cast<Deposit*>(t.get()))
            {
                if (d->getAccountNumber() == acc)
                {
                    deposits += d->getAmount();
                }
            }

            else if (auto w = dynamic_cast<Withdrawal*>(t.get()))
            {
                if (w->getAccountNumber() == acc)
                {
                    withdrawals += w->getAmount();
                }
            }

            else if (auto tr = dynamic_cast<Transfer*>(t.get()))
            {
                if (tr->getAccountNumber() == acc)
                {
                    sent += tr->getAmount();
                }

                if (tr->getReceiverAccount() == acc)
                {
                    received += tr->getAmount();
                }
            }
        }

        cout << "\n========== ACCOUNT STATEMENT ==========\n";

        cout << fixed << setprecision(2);

        cout << "\nAccount Number: " << acc;
        cout << "\nTotal Deposits: Rs. " << deposits;
        cout << "\nTotal Withdrawals: Rs. " << withdrawals;
        cout << "\nTransfers Sent: Rs. " << sent;
        cout << "\nTransfers Received: Rs. " << received;
        cout << "\nCurrent Balance: Rs. " << balances.at(acc);
        cout << endl;
    }

    // ======================================
    // INTEREST CALCULATION
    // ======================================

    double calculateInterest(double balance, double rate, double years)
    {
        if (balance < 0 || rate < 0 || years < 0)
        {
            cout << "\nInvalid interest calculation values!";
            return 0;
        }

        // Simple Interest Formula
        double interest = (balance * rate * years) / 100;

        return interest;
    }

    // ======================================
    // DISPLAY ACCOUNT BALANCES
    // ======================================

    void displayBalances() const
    {
        cout << "\n========== ACCOUNT BALANCES ==========\n";

        cout << fixed << setprecision(2);

        for (const auto &account : balances)
        {
            cout << "\nAccount Number: " << account.first;
            cout << "\nBalance: Rs. " << account.second << endl;
        }
    }
};

// ==========================================
// MAIN FUNCTION
// ==========================================

int main()
{
    TransactionManager manager;

    int choice;

    do
    {
        cout << "\n\n====================================";
        cout << "\n       BANKING MANAGEMENT SYSTEM";
        cout << "\n       MEMBER 3 - TRANSACTIONS";
        cout << "\n====================================";

        cout << "\n1. Record Deposit";
        cout << "\n2. Record Withdrawal";
        cout << "\n3. Money Transfer";
        cout << "\n4. Transaction History";
        cout << "\n5. Account Statement";
        cout << "\n6. Calculate Interest";
        cout << "\n7. Display Account Balances";
        cout << "\n8. Add New Account";
        cout << "\n9. Exit";

        cout << "\n\nEnter your choice: ";

        if (!(cin >> choice))
        {
            cout << "\nInvalid input!";
            break;
        }

        int acc, sender, receiver;
        double amount, rate, years;

        switch (choice)
        {
            case 1:

                cout << "\nEnter account number: ";
                cin >> acc;

                cout << "Enter deposit amount: ";
                cin >> amount;

                manager.recordDeposit(acc, amount);

                break;

            case 2:

                cout << "\nEnter account number: ";
                cin >> acc;

                cout << "Enter withdrawal amount: ";
                cin >> amount;

                manager.recordWithdrawal(acc, amount);

                break;

            case 3:

                cout << "\nEnter sender account: ";
                cin >> sender;

                cout << "Enter receiver account: ";
                cin >> receiver;

                cout << "Enter transfer amount: ";
                cin >> amount;

                manager.transferMoney(sender, receiver, amount);

                break;

            case 4:

                manager.displayHistory();

                break;

            case 5:

                cout << "\nEnter account number: ";
                cin >> acc;

                manager.generateStatement(acc);

                break;

            case 6:

                cout << "\nEnter account balance: ";
                cin >> amount;

                cout << "Enter interest rate (%): ";
                cin >> rate;

                cout << "Enter number of years: ";
                cin >> years;

                cout << "\nCalculated Interest: Rs. "
                     << manager.calculateInterest(amount, rate, years);

                break;

            case 7:

                manager.displayBalances();

                break;

            case 8:

                cout << "\nEnter new account number: ";
                cin >> acc;

                cout << "Enter opening balance: ";
                cin >> amount;

                manager.addAccount(acc, amount);

                break;

            case 9:

                cout << "\nThank you for using Banking Management System!";
                break;

            default:

                cout << "\nInvalid choice!";
        }

    } while (choice != 9);

    return 0;
}
