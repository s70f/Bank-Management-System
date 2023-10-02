#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include "Account.h"

using namespace std;

// Function Prototypes
bool login(vector<vector<string>>);
void staff_options();
void customer_options();
void menu_options();
void header(string);
Account &get_account(vector<Account>);

// User login information
vector<vector<string>> staff_login{
    {"Elon Musk", "1234"}};
vector<vector<string>> customer_login{};

vector<Account> customer_accounts{};

Account &get_account(vector<Account> &accounts, string email)
{

    for (Account &customer : accounts)
    {
        if (email == customer.get_info("email"))
        {

            return customer;
        }
    }
    throw std::runtime_error("Account not found");
}

void header(string text)
{
    string header(10, '=');
    cout << endl;
    cout << header << " " << text << " " << header << endl;
}

bool login(vector<vector<string>> user_pwds)
{
    cout << "Please enter your username: " << endl;

    string username{};
    getline(cin, username);

    cout << "Please enter your password: " << endl;

    string password{};
    getline(cin, password);

    bool access_granted{false};

    for (const vector<string> &login : user_pwds)
    {
        if (login[0] == username && login[1] == password)
            access_granted = true;
    }

    if (access_granted)
        return true;
    else
    {
        cout << "\nIncorrect Login Information" << endl;
        return false;
    }
}

void menu_options()
{
    int condition{0};

    while (condition != 3)
    {
        header("Bank of SESE");
        cout << "How do you want to sign in?" << endl;
        cout << "1-STAFF\n"
             << "2-CUSTOMER\n"
             << "3-QUIT" << endl;
        cin >> condition;

        cin.ignore();

        switch (condition)
        {

        case 1:
            cout << "\nHere is the Staff sign in" << endl;
            if (login(staff_login))
                staff_options();
            break;
        case 2:
            cout << "\nHere is the Customer sign in" << endl;
            if (login(customer_login))
                customer_options();
            break;
        default:
            cout << "\nYou quit" << endl;
            condition = 3;
            break;
        }
    }
}

void customer_options()
{
    string customer_email{};

    // Prompt for and verify customer's email
    cout << "Please confirm your customer's email: " << endl;
    cin >> customer_email;

    try
    {
        Account &customer_account = get_account(customer_accounts, customer_email);

        bool inCustomerPortal = true;

        while (inCustomerPortal)
        {
            header("Customer Portal");
            cout << "Choose an option: " << endl;
            cout << "1-DEPOSIT\n"
                 << "2-WITHDRAW\n"
                 << "3-HISTORY\n"
                 << "4-QUIT" << endl;

            int condition{0};
            cin >> condition;
            cin.ignore();

            switch (condition)
            {
            case 1:
            {
                // Deposit functionality
                int deposit{0};
                cout << "\nYour account limit is $3000" << endl;
                cout << "How much do you want to deposit?" << endl;

                do
                {
                    cin >> deposit;
                    if (deposit <= 3000)
                    {
                        customer_account.change_info("debit", deposit);
                        customer_account.add_history("added", to_string(deposit));
                    }
                    else
                    {
                        cout << "\nYou are $" << deposit - 3000 << " over the limit" << endl;
                        cout << "Please try again, or deposit $0" << endl;
                    }
                } while (deposit > 3000);
                break;
            }
            case 2:
            {
                // Withdraw functionality
                int withdraw{0};
                int debit{get_account(customer_accounts, customer_email).get_info_int("debit")};
                cout << "\nYour withdraw limit is $" << debit << endl;
                cout << "How much do you want to withdraw?" << endl;

                do
                {
                    cin >> withdraw;
                    if (static_cast<int>(withdraw) <= debit && static_cast<int>(withdraw) > 0)
                    {
                        customer_account.change_info("debit", (withdraw * -1));
                        customer_account.add_history("removed", to_string(withdraw));
                    }
                    else
                    {
                        cout << "\nYou are $" << withdraw - debit << " over the limit" << endl;
                        cout << "Please try again, or withdraw $0" << endl;
                    }
                } while (withdraw > debit);
                break;
            }
            case 3:
            {
                // History functionality

                customer_account.get_history();
                break;
            }
            case 4:
            {
                cout << "\nYou Quit" << endl;
                inCustomerPortal = false; // Exit the customer portal loop
                cin.clear();
                break;
            }
            default:
            {
                cout << "Invalid option" << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            }
            }
        }
    }
    catch (const std::runtime_error &)
    {
        cout << "Email not found. Please try again later." << endl;
    }
}
void staff_options()
{
    int condition{0};

    while (condition != 4)
    {
        header("Staff Portal");
        cout << "Choose an option: " << endl;
        cout << "1-CREATE ACCOUNT\n"
             << "2-ACCESS ACOUNT INFORMATION\n"
             << "3-CHANGE ACCOUNT INFORMATION\n"
             << "4-QUIT" << endl;

        cin >> condition;

        switch (condition)
        {
        case 1:
        {
            header("Create New Customer Account");

            // Account information
            string email;
            string name;
            string address;
            string number;
            string password;

            cin.ignore();

            cout << "\nPlease provide a valid email adress: " << endl;
            getline(cin, email);

            cout << "\nPlease provide a name: " << endl;
            getline(cin, name);

            cout << "\nPlease provide a valid address: " << endl;
            getline(cin, address);

            cout << "\nPlease provide a valid phone number: " << endl;
            getline(cin, number);

            cout << "\nPlease create a strong password: " << endl;
            getline(cin, password);

            Account customer_account(name, email, address, password, number);

            customer_accounts.push_back(customer_account);
            vector<string> login_info = {email, password};
            customer_login.push_back(login_info);

            cout << "\nAccount created for " << name << endl;

            break;
        }
        case 2:
        {
            cin.ignore();

            string customer_email;
            cout << "Enter Customer email: ";
            cin >> customer_email;

            bool found = false;

            for (Account customer : customer_accounts)
            {
                if (customer_email == customer.get_info("email"))
                {
                    header("Customer Information");
                    cout << "Name: " << customer.get_info("name") << endl;
                    cout << "Email Address: " << customer.get_info("email") << endl;
                    cout << "Address: " << customer.get_info("address") << endl;
                    cout << "Number: " << customer.get_info("number") << endl;
                    cout << "Debit: $" << customer.get_info("debit") << endl;

                    found = true;
                    break;
                }
            }

            if (!found)
            {
                cout << "Invalid email address" << endl;
            }
            break;
        }
        case 3:
        {
            cin.ignore();

            string customer_email;
            cout << "Enter Customer email: ";
            cin >> customer_email;

            bool found = false;
            for (Account &customer : customer_accounts)
            {
                if (customer_email == customer.get_info("email"))
                {
                    found = true;
                    header("Customer Information");
                    cout << "Name: " << customer.get_info("name") << endl;
                    cout << "Address: " << customer.get_info("address") << endl;
                    cout << "Number: " << customer.get_info("number") << endl;
                    cout << "Debit: $" << customer.get_info("debit") << endl;

                    string information;
                    cout << "What information do you want to change: " << endl;
                    cin >> information;

                    if (information == "Name" || information == "Address" || information == "Number")
                    {
                        string new_info;
                        cout << "\nPlease enter new " << information << " : " << endl;
                        cin >> new_info;

                        string old_info = customer.get_info(information);
                        customer.change_info(information, new_info);
                    }
                    cout << "\nIncorrect Type, try: Name, Adress, or Number" << endl;
                    cout << "Returning to Staff Portal" << endl;
                    break; // Exit the loop after changing information
                }
            }

            if (!found)
            {
                cout << "Invalid email address" << endl;
            }
            break; // Exit the switch case after processing
        }
        default:
            cout << "Exiting Staff Portal" << endl;
            condition = 4;
            cin.clear();
            cin.ignore();

            break;
        }
    }
}

int main()
{
    // Display Menu
    menu_options();

    return 0;
}