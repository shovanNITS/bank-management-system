#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>
using namespace std;

class BankAccount
{
private:
    string name;
    long long accountNum;
    double balance;
    string address;
    long long phone;
    int pinCode;

public:
    BankAccount(string n, long long ac, double bal, string addr, long long ph, int pin) : name(n), accountNum(ac), balance(bal), address(addr), phone(ph), pinCode(pin) {}

    string getName() const
    {
        return name;
    }

    long long getAccountNum() const
    {
        return accountNum;
    }

    double getBalance() const
    {
        return balance;
    }

    string getAddress() const
    {
        return address;
    }

    long long getPhone() const
    {
        return phone;
    }

    int getPinCode() const
    {
        return pinCode;
    }

    void setName(const string &newName)
    {
        name = newName;
    }

    void setBalance(double newBalance)
    {
        balance = newBalance;
    }

    void setAddress(const string &newAddress)
    {
        address = newAddress;
    }

    void setPhone(long long newPhone)
    {
        phone = newPhone;
    }

    void setPinCode(int newPin)
    {
        pinCode = newPin;
    }

    void deposit(double amount)
    {
        balance += amount;
    }

    void withdraw(double amount)
{
    if (balance >= amount)
    {
        balance -= amount;
        cout << "\t\tWithdraw Successfully..." << endl;
    }
    else
    {
        cout << "\t\tInsufficient Balance...." << endl;
    }
}

};

class BankManagement
{
private:
    vector<BankAccount> accounts;
    string filename;

    void writeToFile()
    {
        ofstream outFile(filename);
        if (outFile.is_open())
        {
            for (const auto &acc : accounts)
            {
                outFile << acc.getName() << "," << acc.getAccountNum() << "," << acc.getBalance() << "," << acc.getAddress() << "," << acc.getPhone() << "," << acc.getPinCode() << endl;
            }
            outFile.close();
        }
        else
        {
            cout << "Error: Unable to write to file." << endl;
        }
    }

    void readFromFile()
    {
        ifstream inFile(filename);
        if (inFile.is_open())
        {
            string line;
            while (getline(inFile, line))
            {
                stringstream ss(line);
                string name, address;
                double balance;
                long long accountNum, phone;
                int pincode;

                getline(ss, name, ',');
                ss >> accountNum;
                ss.ignore();
                ss >> balance;
                ss.ignore();
                getline(ss, address, ',');
                ss >> phone;
                ss.ignore();
                ss >> pincode;

                accounts.push_back(BankAccount(name, accountNum, balance, address, phone, pincode));
            }
            inFile.close();
        }
        else
        {
            cout << "Error: Unable to read from file." << endl;
        }
    }

public:
    BankManagement(string fname) : filename(fname)
    {
        readFromFile();
    }

    ~BankManagement()
    {
        writeToFile();
    }

    void AddAccount(const string &name, long long accountNum, double balance, const string &address, long long phone, int pinCode)
    {
        accounts.push_back(BankAccount(name, accountNum, balance, address, phone, pinCode));
        writeToFile();
    }

    void showAllAccounts() const
    {
        cout << "\t\tALL ACCOUNT HOLDERS" << endl
             << endl;
        for (const auto &acc : accounts)
        {
            cout << "\t\tName: " << acc.getName() << " \n\t\tAccount Number: " << acc.getAccountNum() << " \n\t\tBalance: " << acc.getBalance() << endl;
            cout << "\t\tAddress: " << acc.getAddress() << " \n\t\tPhone Number: " << acc.getPhone() << endl;
            cout << "\t\tPin Code: " << acc.getPinCode() << endl;
            cout << "\t\tIFSC Code: ABCIN0000056" << endl;
            cout << endl;
        }
    }

    void searchAccount(long long account) const
    {
        cout << "\t\tAccount Holder " << endl;
        for (const auto &acc : accounts)
        {
            if (acc.getAccountNum() == account)
            {
                cout << "\t\tName: " << acc.getName() << "\n\t\tAccount Number: " << acc.getAccountNum() << " \n\t\tBalance: " << acc.getBalance() << endl;
                cout << "\t\tAddress: " << acc.getAddress() << " \n\t\tPhone Number: " << acc.getPhone() << endl;
                cout << "\t\tPin Code: " << acc.getPinCode() << endl;
                cout << "\t\tIFSC Code: ABCIN0000056" << endl;
            }
        }
    }

    BankAccount *findAccount(long long accountNum)
    {
        for (auto &acc : accounts)
        {
            if (acc.getAccountNum() == accountNum)
            {
                return &acc;
            }
        }
        return nullptr;
    }

    void updateAccount(long long accountNum)
    {
        BankAccount *account = findAccount(accountNum);
        if (account != nullptr)
        {
            int choice;
            do
            {
                cout << "\t\t1. Update Name" << endl;
                cout << "\t\t2. Update Balance" << endl;
                cout << "\t\t3. Update Phone Number" << endl;
                cout << "\t\t4. Update Address" << endl;
                cout << "\t\t5. Update Pin Code" << endl;
                cout << "\t\t6. Exit" << endl;
                cout << "\t\tEnter Your Choice :";
                cin >> choice;
                switch (choice)
                {
                case 1:
                {
                    string newName;
                    cout << "\t\tEnter New Name :";
                    cin.ignore();
                    getline(cin, newName);
                    account->setName(newName);
                    cout << "\t\tName Updated Successfully ...." << endl;
                    break;
                }
                case 2:
                {
                    double newBalance;
                    cout << "\t\tEnter New Balance :";
                    cin >> newBalance;
                    account->setBalance(newBalance);
                    cout << "\t\tBalance Updated Successfully ...." << endl;
                    break;
                }
                case 3:
                {
                    long long newPhone;
                    cout << "\t\tEnter New Phone Number :";
                    cin >> newPhone;
                    account->setPhone(newPhone);
                    cout << "\t\tPhone Number Updated Successfully ...." << endl;
                    break;
                }
                case 4:
                {
                    string newAddress;
                    cout << "\t\tEnter New Address :";
                    cin.ignore();
                    getline(cin, newAddress);
                    account->setAddress(newAddress);
                    cout << "\t\tAddress Updated Successfully ...." << endl;
                    break;
                }
                case 5:
                {
                    int newPin;
                    cout << "\t\tEnter New Pin Code :";
                    cin >> newPin;
                    account->setPinCode(newPin);
                    cout << "\t\tPin Code Updated Successfully ...." << endl;
                    break;
                }
                case 6:
                {
                    break;
                }
                default:
                {
                    cout << "\t\tInvalid Choice...." << endl;
                    break;
                }
                }
            } while (choice != 6);
        }
        else
        {
            cout << "\t\tAccount Not Found ..." << endl;
        }
    }
};

int main()
{
    BankManagement bank("userData.txt");
    int choice;
    char op;
    do
    {
        system("cls");
        cout << "\t\t::Bank Management System" << endl;
        cout << "\t\t\tMain Menu" << endl;
        cout << "\t\t1. Create New Account" << endl;
        cout << "\t\t2. Show All Account" << endl;
        cout << "\t\t3. Search Account" << endl;
        cout << "\t\t4. Deposit Money" << endl;
        cout << "\t\t5. Withdraw Money" << endl;
        cout << "\t\t6. Update Account Records" << endl;
        cout << "\t\t7. Exit" << endl;
        cout << "\t\t-------------------------------" << endl;
        cout << "\t\tEnter Your Choice :";
        cin >> choice;
        switch (choice)
        {
        case 1:
        {
            srand(time(0)); 
            long long accountNumber = 0;
            for (int i = 0; i < 6; ++i)
            {
                accountNumber = accountNumber * 10 + (rand() % 10);
            }
            string name;
            double balance;
            long long int phoneNo;
            int pincode;
            string address;
            cout << "\t\tEnter Name :";
            cin.ignore();
            getline(cin, name);
            cout << "\t\tEnter phone number :";
            cin >> phoneNo;
            cout << "\t\tEnter pincode :";
            cin >> pincode;
            cout << "\t\tEnter address :";
            cin.ignore();
            getline(cin, address);
            cout << "\t\tEnter Initial Balance :";
            cin >> balance;
            cout << "\n\t\tAccount Created successfully!\n\n";
            cout << "\t\tYour Account Number:" << accountNumber << endl;
            cout << "\t\tIFSC Code: ABCIN0000056" << endl; 
            bank.AddAccount(name, accountNumber, balance, address, phoneNo, pincode);
            cout << "\t\tInitial Balance:" << balance << endl;
            break;
        }
        case 2:
        {
            bank.showAllAccounts();
            break;
        }
        case 3:
        {
            long long accountNum;
            cout << "Enter Account Number :";
            cin >> accountNum;
            bank.searchAccount(accountNum);
            break;
        }
        case 4:
        {
            long long accountNum;
            double amount;
            cout << "\t\tEnter Account Number to Deposit Money :";
            cin >> accountNum;
            BankAccount *account = bank.findAccount(accountNum);
            if (account != nullptr)
            {
                cout << "\t\tEnter Amount to Deposit(in Rs) :";
                cin >> amount;
                account->deposit(amount);
                cout << "\t\tRs" << amount << " Deposited Successfully ...." << endl;
            }
            else
            {
                cout << "\t\tAcount Not Found ..." << endl;
            }
            break;
        }
        case 5:
        {
            long long accountNum;
            double amount;
            cout << "\t\tEnter Account Number to Withdraw Money :";
            cin >> accountNum;
            BankAccount *account = bank.findAccount(accountNum);
            if (account != nullptr)
            {
                cout << "\t\tEnter Amount to withdraw(in Rs):";
                cin >> amount;
                account->withdraw(amount);
                cout << "\t\tRs" << amount << " withdrawn Successfully ...." << endl;
            }
            else
            {
                cout << "\t\tAccount Not Found ..." << endl;
            }
            break;
        }
        case 6:
        {
            long long accountNum;
            cout << "\t\tEnter Account Number to Update Records :";
            cin >> accountNum;
            bank.updateAccount(accountNum);
            break;
        }
        case 7:
        {
            exit(0);
            break;
        }
        default:
        {
            cout << "\t\tInvalid Choice...." << endl;
            break;
        }
        }
        cout << "\t\tDo You Want to Continue or Exit [Yes/No] ??";
        cin >> op;

    } while (op == 'y' || op == 'Y');
    return 0;
}

