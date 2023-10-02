#include "Account.h"
#include <string>
#include <iostream>
#include <vector>

Account::Account(std::string name1, std::string email1, std::string address1, std::string password1, std::string number1) : email{email1}, password{password1}, name{name1}, address{address1}, number{number1}, debit{0}
{
}

Account::Account(std::string email1, std::string password1) : Account{"None", email1, "None", password1, "None "}
{
}

Account::Account()
    : Account{"", "", "", "", ""}
{
}

std::string Account::get_info(std::string info) const
{
    if (info == "email")
        return email;
    if (info == "name")
        return name;
    if (info == "address")
        return address;
    if (info == "email")
        return email;
    if (info == "number")
        return number;
    if (info == "debit")
        return std::to_string(debit);
    else
        return "No Information";
}
int Account::get_info_int(std::string info)
{
    if (info == "debit")
        return debit;
    else
        return 0;
}
void Account::change_info(std::string info, int new_info)
{
    if (info == "debit")
        debit += new_info;
}
void Account::change_info(std::string info, std::string new_info)
{
    bool informationChanged = false;

    if (info == "Name")
    {
        if (name != new_info)
        {
            name = new_info;
            informationChanged = true;
        }
    }
    else if (info == "Email")
    {
        if (email != new_info)
        {
            email = new_info;
            informationChanged = true;
        }
    }
    else if (info == "Address")
    {
        if (address != new_info)
        {
            address = new_info;
            informationChanged = true;
        }
    }
    else if (info == "Number")
    {
        if (number != new_info)
        {
            number = new_info;
            informationChanged = true;
        }
    }
    else if (info == "Password")
    {
        if (password != new_info)
        {
            password = new_info;
            informationChanged = true;
        }
    }
    else
    {
        // Handle the case where 'info' is not recognized
        std::cout << "Invalid information type: " << info << std::endl;
    }

    if (informationChanged)
    {
        std::cout << info << " changed to " << new_info << std::endl;
    }
}

void Account::add_history(std::string action, std::string amount)
{
    std::string transaction{"You " + action + " $" + amount};
    std::cout << transaction << std::endl;
    history.push_back(transaction);
}

void Account::get_history()
{
    size_t vectorSize = history.size();

    size_t transactions{0};
    std::cout << "How many transactions do you want to see: " << std::endl;
    std::cin >> transactions;

    if (transactions <= vectorSize)
    {
        std::cout << "Dispalying " << transactions << " transactions..." << std::endl;
        size_t i{vectorSize - transactions};

        for (; i < vectorSize; ++i)
        {
            std::cout << history[i] << std::endl;
        }
    }
    else
    {
        std::cout << "Invalid number, you have not completed that many transactions" << std::endl;
    }
}