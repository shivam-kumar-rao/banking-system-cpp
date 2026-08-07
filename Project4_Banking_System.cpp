/*
    Project 4: Banking System
    CodeAlpha C++ Programming Internship

    Logic:
    - Three classes used: Customer, Account and Transaction.
    - Customer holds basic customer details (name, id).
    - Account is linked to a Customer, holds balance and account number.
      It has functions for deposit, withdraw and to check balance.
    - Transaction class stores a single record (type, amount) and Account
      keeps a vector of Transaction objects so we can show history later.
    - Transfer is done by withdrawing from one account and depositing in another.
*/

#include <iostream>
#include <vector>
#include <string>
using namespace std;

// ---------------- Customer Class ----------------
class Customer
{
public:
    int customerId;
    string name;

    Customer(int id, string customerName)
    {
        customerId = id;
        name = customerName;
    }
};

// ---------------- Transaction Class ----------------
class Transaction
{
public:
    string type;   // "Deposit", "Withdraw", "Transfer In", "Transfer Out"
    double amount;

    Transaction(string t, double amt)
    {
        type = t;
        amount = amt;
    }
};

// ---------------- Account Class ----------------
class Account
{
public:
    int accountNumber;
    Customer owner;
    double balance;
    vector<Transaction> history;

    Account(int accNo, Customer cust, double initialBalance) : owner(cust)
    {
        accountNumber = accNo;
        balance = initialBalance;
    }

    void deposit(double amount)
    {
        if (amount <= 0)
        {
            cout << "Deposit amount must be positive." << endl;
            return;
        }
        balance += amount;
        history.push_back(Transaction("Deposit", amount));
        cout << "Deposited Rs. " << amount << " successfully. New balance: Rs. " << balance << endl;
    }

    bool withdraw(double amount)
    {
        if (amount <= 0)
        {
            cout << "Withdraw amount must be positive." << endl;
            return false;
        }
        if (amount > balance)
        {
            cout << "Insufficient balance!" << endl;
            return false;
        }
        balance -= amount;
        history.push_back(Transaction("Withdraw", amount));
        cout << "Withdrew Rs. " << amount << " successfully. New balance: Rs. " << balance << endl;
        return true;
    }

    void showBalance()
    {
        cout << "Account No: " << accountNumber << " | Owner: " << owner.name
             << " | Balance: Rs. " << balance << endl;
    }

    void showHistory()
    {
        cout << "\n--- Transaction History for Account " << accountNumber << " ---" << endl;
        if (history.empty())
        {
            cout << "No transactions yet." << endl;
            return;
        }
        for (int i = 0; i < history.size(); i++)
        {
            cout << i + 1 << ". " << history[i].type << " : Rs. " << history[i].amount << endl;
        }
    }
};

// function to transfer money between two accounts
void transferFunds(Account &from, Account &to, double amount)
{
    if (from.withdraw(amount))
    {
        // withdraw already prints its own message, so we adjust the last history entry type
        from.history.back().type = "Transfer Out";
        to.balance += amount;
        to.history.push_back(Transaction("Transfer In", amount));
        cout << "Transfer of Rs. " << amount << " from Account " << from.accountNumber
             << " to Account " << to.accountNumber << " successful." << endl;
    }
    else
    {
        cout << "Transfer failed due to insufficient balance." << endl;
    }
}

int main()
{
    cout << "===== SIMPLE BANKING SYSTEM =====" << endl;

    // creating two customers and their accounts for demo
    Customer cust1(1, "Shivam");
    Customer cust2(2, "Rahul");

    Account acc1(1001, cust1, 5000.0);
    Account acc2(1002, cust2, 2000.0);

    int choice;
    do
    {
        cout << "\n----- MENU -----" << endl;
        cout << "1. Show Account 1 details" << endl;
        cout << "2. Show Account 2 details" << endl;
        cout << "3. Deposit into Account 1" << endl;
        cout << "4. Withdraw from Account 1" << endl;
        cout << "5. Transfer Account 1 -> Account 2" << endl;
        cout << "6. Show Account 1 Transaction History" << endl;
        cout << "7. Show Account 2 Transaction History" << endl;
        cout << "8. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        double amt;

        switch (choice)
        {
        case 1:
            acc1.showBalance();
            break;
        case 2:
            acc2.showBalance();
            break;
        case 3:
            cout << "Enter amount to deposit: ";
            cin >> amt;
            acc1.deposit(amt);
            break;
        case 4:
            cout << "Enter amount to withdraw: ";
            cin >> amt;
            acc1.withdraw(amt);
            break;
        case 5:
            cout << "Enter amount to transfer: ";
            cin >> amt;
            transferFunds(acc1, acc2, amt);
            break;
        case 6:
            acc1.showHistory();
            break;
        case 7:
            acc2.showHistory();
            break;
        case 8:
            cout << "Exiting Banking System. Thank you!" << endl;
            break;
        default:
            cout << "Invalid choice, please try again." << endl;
        }

    } while (choice != 8);

    return 0;
}
