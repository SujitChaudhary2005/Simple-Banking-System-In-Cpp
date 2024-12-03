#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

#define MIN_BALANCE 500

class InsufficientFunds {};

class Account {
private:
    long accountID;
    string firstName;
    string lastName;
    float accountBalance;
    static long nextAccountID;

public:
    Account() {}

    Account(string fName, string lName, float initialBalance) {
        nextAccountID++;
        accountID = nextAccountID;
        firstName = fName;
        lastName = lName;
        accountBalance = initialBalance;
    }

    long getAccountID() const {
        return accountID;
    }

    string getFirstName() const {
        return firstName;
    }

    string getLastName() const {
        return lastName;
    }

    float getBalance() const {
        return accountBalance;
    }

    void deposit(float amount) {
        if (amount <= 0) {
            cout << "Deposit amount must be greater than zero!" << endl;
            return;
        }
        accountBalance += amount;
    }

    void withdraw(float amount) {
        if (amount <= 0) {
            cout << "Withdrawal amount must be greater than zero!" << endl;
            return;
        }
        if (accountBalance - amount < MIN_BALANCE) {
            throw InsufficientFunds();
        }
        accountBalance -= amount;
    }

    static void setLastAccountID(long accountID) {
        nextAccountID = accountID;
    }

    static long getLastAccountID() {
        return nextAccountID;
    }

    friend ofstream& operator<<(ofstream& ofs, const Account& acc) {
        ofs << acc.accountID << endl;
        ofs << acc.firstName << endl;
        ofs << acc.lastName << endl;
        ofs << acc.accountBalance << endl;
        return ofs;
    }

    friend ifstream& operator>>(ifstream& ifs, Account& acc) {
        ifs >> acc.accountID;
        ifs >> acc.firstName;
        ifs >> acc.lastName;
        ifs >> acc.accountBalance;
        return ifs;
    }

    friend ostream& operator<<(ostream& os, const Account& acc) {
        os << "Account ID: " << acc.getAccountID() << endl;
        os << "First Name: " << acc.getFirstName() << endl;
        os << "Last Name: " << acc.getLastName() << endl;
        os << "Balance: " << acc.getBalance() << endl;
        return os;
    }
};

long Account::nextAccountID = 0;

class Bank {
private:
    vector<Account> accountsList;

public:
    Bank() {
        ifstream inFile("BankData.txt");
        if (!inFile) {
            cout << "No previous account data found. Starting fresh!" << endl;
            return;
        }
        Account acc;
        while (inFile >> acc) {
            accountsList.push_back(acc);
        }
        if (!accountsList.empty()) {
            Account::setLastAccountID(accountsList.back().getAccountID());
        }
        inFile.close();
    }

    Account createAccount(string fName, string lName, float initialBalance) {
        if (initialBalance < MIN_BALANCE) {
            cout << "Initial balance must be at least " << MIN_BALANCE << "!" << endl;
            return Account();
        }
        Account newAccount(fName, lName, initialBalance);
        accountsList.push_back(newAccount);
        return newAccount;
    }

    Account getAccountDetails(long accountID) {
        for (int i = 0; i < accountsList.size(); i++) {
            if (accountsList[i].getAccountID() == accountID) {
                return accountsList[i];
            }
        }
        throw runtime_error("Account not found!");
    }

    Account depositToAccount(long accountID, float amount) {
        for (int i = 0; i < accountsList.size(); i++) {
            if (accountsList[i].getAccountID() == accountID) {
                accountsList[i].deposit(amount);
                return accountsList[i];
            }
        }
        throw runtime_error("Account not found!");
    }

    Account withdrawFromAccount(long accountID, float amount) {
        for (int i = 0; i < accountsList.size(); i++) {
            if (accountsList[i].getAccountID() == accountID) {
                accountsList[i].withdraw(amount);
                return accountsList[i];
            }
        }
        throw runtime_error("Account not found!");
    }

    void closeAccount(long accountID) {
        for (int i = 0; i < accountsList.size(); i++) {
            if (accountsList[i].getAccountID() == accountID) {
                accountsList.erase(accountsList.begin() + i);
                cout << "Account closed successfully!" << endl;
                return;
            }
        }
        throw runtime_error("Account not found!");
    }

    void displayAllAccounts() {
        if (accountsList.empty()) {
            cout << "No accounts to display!" << endl;
            return;
        }
        for (int i = 0; i < accountsList.size(); i++) {
            cout << accountsList[i] << endl;
        }
    }

    ~Bank() {
        ofstream outFile("BankData.txt");
        for (int i = 0; i < accountsList.size(); i++) {
            outFile << accountsList[i];
        }
        outFile.close();
    }
};

int main() {
    Bank bank;
    int choice;
    string firstName, lastName;
    long accountID;
    float balance, amount;

    cout << "Welcome to the Simple Banking System!" << endl;

    do {
        cout << "\nMenu:\n";
        cout << "1. Open Account\n";
        cout << "2. Balance Enquiry\n";
        cout << "3. Deposit\n";
        cout << "4. Withdraw\n";
        cout << "5. Close Account\n";
        cout << "6. Show All Accounts\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter First Name: ";
            cin >> firstName;
            cout << "Enter Last Name: ";
            cin >> lastName;
            cout << "Enter Initial Balance: ";
            cin >> balance;
            bank.createAccount(firstName, lastName, balance);
            break;

        case 2:
            cout << "Enter Account ID: ";
            cin >> accountID;
            try {
                cout << bank.getAccountDetails(accountID);
            } catch (runtime_error& e) {
                cout << "Error: " << e.what() << endl;
            }
            break;

        case 3:
            cout << "Enter Account ID: ";
            cin >> accountID;
            cout << "Enter Deposit Amount: ";
            cin >> amount;
            try {
                cout << bank.depositToAccount(accountID, amount);
            } catch (runtime_error& e) {
                cout << "Error: " << e.what() << endl;
            }
            break;

        case 4:
            cout << "Enter Account ID: ";
            cin >> accountID;
            cout << "Enter Withdrawal Amount: ";
            cin >> amount;
            try {
                cout << bank.withdrawFromAccount(accountID, amount);
            } catch (runtime_error& e) {
                cout << "Error: " << e.what() << endl;
            }
            break;

        case 5:
            cout << "Enter Account ID: ";
            cin >> accountID;
            try {
                bank.closeAccount(accountID);
            } catch (runtime_error& e) {
                cout << "Error: " << e.what() << endl;
            }
            break;

        case 6:
            bank.displayAllAccounts();
            break;

        case 7:
            cout << "Thank you for using the Banking System!" << endl;
            break;

        default:
            cout << "Invalid choice. Please try again!" << endl;
        }
    } while (choice != 7);

    return 0;
}