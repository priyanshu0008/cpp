#include <iostream>
#include <string>
#include <unordered_map>

class ATM {
private:
    std::unordered_map<std::string, double> accounts;
    std::string current_account;

    void displayMenu() {
        std::cout << "ATM Menu:\n";
        std::cout << "1. Check Balance\n";
        std::cout << "2. Deposit Money\n";
        std::cout << "3. Withdraw Money\n";
        std::cout << "4. Exit\n";
    }

    void checkBalance() {
        std::cout << "Current balance: $" << accounts[current_account] << "\n";
    }

    void depositMoney() {
        double amount;
        std::cout << "Enter amount to deposit: $";
        std::cin >> amount;
        if (amount > 0) {
            accounts[current_account] += amount;
            std::cout << "Deposited: $" << amount << "\n";
        } else {
            std::cout << "Invalid amount.\n";
        }
    }

    void withdrawMoney() {
        double amount;
        std::cout << "Enter amount to withdraw: $";
        std::cin >> amount;
        if (amount > 0 && amount <= accounts[current_account]) {
            accounts[current_account] -= amount;
            std::cout << "Withdrew: $" << amount << "\n";
        } else {
            std::cout << "Invalid amount or insufficient funds.\n";
        }
    }

public:
    ATM() {
        // Initializing with some dummy accounts
        accounts["1234"] = 500.0;
        accounts["5678"] = 1000.0;
    }

    void login() {
        std::string account_number;
        std::cout << "Enter account number: ";
        std::cin >> account_number;
        if (accounts.find(account_number) != accounts.end()) {
            current_account = account_number;
            std::cout << "Login successful.\n";
        } else {
            std::cout << "Account not found.\n";
        }
    }

    void run() {
        if (current_account.empty()) {
            login();
        }
        if (!current_account.empty()) {
            int choice;
            do {
                displayMenu();
                std::cout << "Enter your choice: ";
                std::cin >> choice;
                switch (choice) {
                    case 1:
                        checkBalance();
                        break;
                    case 2:
                        depositMoney();
                        break;
                    case 3:
                        withdrawMoney();
                        break;
                    case 4:
                        std::cout << "Exiting...\n";
                        break;
                    default:
                        std::cout << "Invalid choice. Try again.\n";
                }
            } while (choice != 4);
        }
    }
};

int main() {
    
    ATM atm;
    atm.run();
    return 0;
}