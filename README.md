
# 🏦 Simple Banking System

Welcome to the **Simple Banking System**, a C++ application that simulates basic banking functionalities. This program allows users to manage accounts, make transactions, and view account details. It is designed to be simple yet effective, providing a console-based interface for user interaction.

---

## 📜 Features

### Account Management
- **Create New Accounts** 🆕: Open a new account with a minimum balance of $500.
- **Close Accounts** ❌: Remove an account from the system.

### Transactions
- **Deposit Money** 💰: Add funds to an account.
- **Withdraw Money** 🏧: Withdraw funds while maintaining a minimum balance.

### Account Information
- **View Account Details** 🧐: Check account information like balance, account ID, and holder's name.
- **Display All Accounts** 📋: List details of all existing accounts.

### Data Persistence
- **Save and Load Data** 💾: Automatically saves account data to a file (`BankData.txt`) and reloads it on the next program execution.

---

## 🚀 Getting Started

### Prerequisites
- A C++ compiler like `g++`.

### Compilation
To compile the program, use:
```bash
g++ -o BankingSystem BankingSystem.cpp
```

### Running the Program
After compiling, run the program with:

```bash
./BankingSystem
```

---

## 📋 Menu Options
Upon running the program, you'll be presented with the following menu:

1. **Open Account** 🆕  
   Create a new account by providing the holder's first name, last name, and initial balance.

2. **Balance Enquiry** 🧐  
   Retrieve details of an account by entering its ID.

3. **Deposit** 💰  
   Add funds to an account by specifying its ID and deposit amount.

4. **Withdraw** 🏧  
   Withdraw funds from an account while ensuring the balance does not fall below ₹500.

5. **Close Account** ❌  
   Permanently remove an account from the system by entering its ID.

6. **Show All Accounts** 📋  
   View details of all accounts in the system.

7. **Exit** 🚪  
   Save all data and exit the program.

---

## 🛠️ How It Works

### Class Overview

#### Account Class
Manages individual account details.

**Attributes**:
- `accountID`: Unique identifier for each account.
- `firstName` and `lastName`: Account holder's name.
- `accountBalance`: Current account balance.

**Functionalities**:
1. **Constructor**:
   - Initializes a new account by accepting the user's `first name`, `last name`, and an initial balance. 
   - Assigns a unique `accountID` using `nextAccountID`.
   
2. **Getter Methods**:
   - Methods like `getAccountID()`, `getFirstName()`, `getLastName()`, and `getBalance()` return the respective account details.

3. **Transaction Methods**:
   - `deposit(float amount)`: Adds the specified amount to the account balance. Prints an error if the amount is zero or negative.
   - `withdraw(float amount)`: Deducts the specified amount, ensuring the balance doesn't fall below `MIN_BALANCE`. Throws an `InsufficientFunds` exception if the rule is violated.

4. **Static Methods**:
   - `setLastAccountID(long accountID)`: Updates the `nextAccountID` value.
   - `getLastAccountID()`: Returns the current value of `nextAccountID`.

5. **Overloaded Operators**:
   - `operator<< (ofstream)`: Saves account details to a file.
   - `operator>> (ifstream)`: Loads account details from a file.
   - `operator<< (ostream)`: Displays account information in the console.

---

#### Bank Class
Manages multiple accounts.

**Attributes**:
- `accountsList`: A vector that stores all account objects.

**Functionalities**:
1. **Constructor**:
   - Attempts to load account data from `BankData.txt`. If the file doesn't exist, starts with an empty list.

2. **Account Management**:
   - `createAccount(string fName, string lName, float initialBalance)`: Adds a new account to the list.
   - `getAccountDetails(long accountID)`: Retrieves an account's details using its ID.
   - `closeAccount(long accountID)`: Removes an account from the list.

3. **Transaction Methods**:
   - `depositToAccount(long accountID, float amount)`: Adds funds to an account.
   - `withdrawFromAccount(long accountID, float amount)`: Withdraws funds, enforcing the minimum balance rule.

4. **Utility**:
   - `displayAllAccounts()`: Displays all accounts in the system.

5. **Destructor**:
   - Saves all account data to `BankData.txt` when the program exits.

---

## 🔎 Detailed Explanation of the Code

### 1. Header Files and Definitions
```cpp
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#define MIN_BALANCE 500
```
**Header Files**(libraries):
This project utilizes the following C++ standard libraries:

   1. **`<iostream>`** for input/output operations:
      - `cout` for output
      - `cin` for input
      - `endl` for line breaks and flushing output

   2. **`<vector>`** for dynamic array management:
      - `push_back()`, `size()`, `empty()`, `begin()`, `end()`, `erase()`

   3. **`<fstream>`** for file handling:
      - `ofstream` for writing to files
      - `ifstream` for reading from files
      - `operator<<` and `operator>>` for file input/output

   4. **`<string>`** for string handling:
      - `string` for text storage and manipulation
      - `operator<<` and `operator>>` for string input/output

   5. **`<stdexcept>`** for error handling:
      - `runtime_error` for exception handling (e.g., account not found)

**Definitions**:
  - `MIN_BALANCE`: The minimum balance required in an account.
  
### 2. Custom Exception Class
```cpp
class InsufficientFunds {};
```
- Used to handle withdrawal attempts that violate the minimum balance rule.

### 3. Main Function
```cpp
int main() {
    Bank bank;
    int choice;
    string firstName, lastName;
    long accountID;
    float balance, amount;
```
The `main()` function provides a menu for the user to interact with the system. It handles:
- Account creation.
- Balance enquiry.
- Deposits and withdrawals.
- Account closure.
- Displaying all accounts.

**NOTE**: The program runs in a loop until the user selects "Exit."

---

## 📂 File Structure

```
Simple-Banking-System-In-Cpp/
├── BankingSystem.cpp   # Contains the entire code
├── BankData.txt        # Created during runtime if it doesn't already exist; stores account data
├── BankingSystem.exe   # Executable file generated after compilation
├── README.md           # Project description with usage instructions
├── LICENSE             # License file for the project
```

---

## 💡 Tips

- Ensure the initial balance meets the minimum requirement to open an account.
- Use valid IDs when performing transactions or retrieving account details.
- Safeguard the `BankData.txt` file for seamless functionality across sessions.

---

## 🔗 License

This project is licensed under the MIT License. Feel free to use, modify, and distribute it as needed, but attribution is appreciated!