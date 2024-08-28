#include <iostream>
#include <vector>
#include <string>
#include <limits>

using namespace std;

// Class to represent a bank account
class Account {
private:
    int accountNumber;
    string accountHolder;
    double balance;

public:
    Account(int accNum, const string& holder, double initialBalance)
        : accountNumber(accNum), accountHolder(holder), balance(initialBalance) {}

    int getAccountNumber() const { return accountNumber; }
    const string& getAccountHolder() const { return accountHolder; }
    double getBalance() const { return balance; }

    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << "Deposited: $" << amount << endl;
        } else {
            cout << "Deposit amount must be positive." << endl;
        }
    }

    bool withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            cout << "Withdrawn: $" << amount << endl;
            return true;
        } else {
            cout << (amount <= 0 ? "Withdrawal amount must be positive." : "Insufficient balance.") << endl;
            return false;
        }
    }

    bool transfer(Account& toAccount, double amount) {
        if (withdraw(amount)) {
            toAccount.deposit(amount);
            cout << "Transferred: $" << amount << " to Account: " << toAccount.getAccountNumber() << endl;
            return true;
        }
        return false;
    }

    void printAccountInfo() const {
        cout << "Account Number: " << accountNumber << endl;
        cout << "Account Holder: " << accountHolder << endl;
        cout << "Balance: $" << balance << endl;
    }
};

// Class to manage the bank system
class BankSystem {
private:
    vector<Account> accounts;
    int nextAccountNumber = 1000;

    Account* findAccount(int accountNumber) {
        for (auto& acc : accounts) {
            if (acc.getAccountNumber() == accountNumber) {
                return &acc;
            }
        }
        return nullptr;
    }

    void clearInput() {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

public:
    void createAccount() {
        string holder;
        double initialBalance;

        cout << "Enter account holder name: ";
        cin.ignore();
        getline(cin, holder);

        cout << "Enter initial deposit amount: ";
        while (!(cin >> initialBalance) || initialBalance < 0) {
            cout << "Invalid amount. Please enter a positive number: ";
            clearInput();
        }

        Account newAccount(nextAccountNumber++, holder, initialBalance);
        accounts.push_back(newAccount);
        cout << "Account created successfully!" << endl;
        newAccount.printAccountInfo();
    }

    void depositFunds() {
        int accNum;
        double amount;

        cout << "Enter account number: ";
        while (!(cin >> accNum) || findAccount(accNum) == nullptr) {
            cout << "Invalid account number. Please try again: ";
            clearInput();
        }

        cout << "Enter deposit amount: ";
        while (!(cin >> amount) || amount <= 0) {
            cout << "Invalid amount. Please enter a positive number: ";
            clearInput();
        }

        Account* account = findAccount(accNum);
        account->deposit(amount);
        account->printAccountInfo();
    }

    void withdrawFunds() {
        int accNum;
        double amount;

        cout << "Enter account number: ";
        while (!(cin >> accNum) || findAccount(accNum) == nullptr) {
            cout << "Invalid account number. Please try again: ";
            clearInput();
        }

        cout << "Enter withdrawal amount: ";
        while (!(cin >> amount) || amount <= 0) {
            cout << "Invalid amount. Please enter a positive number: ";
            clearInput();
        }

        Account* account = findAccount(accNum);
        account->withdraw(amount);
        account->printAccountInfo();
    }

    void transferFunds() {
        int fromAccNum, toAccNum;
        double amount;

        cout << "Enter source account number: ";
        while (!(cin >> fromAccNum) || findAccount(fromAccNum) == nullptr) {
            cout << "Invalid source account number. Please try again: ";
            clearInput();
        }

        cout << "Enter target account number: ";
        while (!(cin >> toAccNum) || findAccount(toAccNum) == nullptr) {
            cout << "Invalid target account number. Please try again: ";
            clearInput();
        }

        cout << "Enter transfer amount: ";
        while (!(cin >> amount) || amount <= 0) {
            cout << "Invalid amount. Please enter a positive number: ";
            clearInput();
        }

        Account* fromAccount = findAccount(fromAccNum);
        Account* toAccount = findAccount(toAccNum);

        if (fromAccount && toAccount) {
            fromAccount->transfer(*toAccount, amount);
            fromAccount->printAccountInfo();
            toAccount->printAccountInfo();
        } else {
            cout << "One or both account numbers not found." << endl;
        }
    }

    void displayMenu() {
        int choice;
        do {
            cout << "\nBank System Menu:\n";
            cout << "1. Create Account\n";
            cout << "2. Deposit Funds\n";
            cout << "3. Withdraw Funds\n";
            cout << "4. Tran
