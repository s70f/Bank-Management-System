#ifndef _ACCOUNT_H_
#define _ACCOUNT_H_
#include <string>
#include <vector>

class Account
{
private:
    // Attributes
    // name, email, pwd, number, address

    std::string email;
    std::string password;
    std::string name;
    std::string address;
    std::string number;
    int debit{0};
    std::vector<std::string> history{};

public:
    Account(std::string name1, std::string email1, std::string address1, std::string password1, std::string number1);
    Account(std::string email1, std::string password1);
    Account();

    std::string get_info(std::string) const;
    int get_info_int(std::string);
    void change_info(std::string, std::string);
    void change_info(std::string info, int new_info);
    void add_history(std::string action, std::string amount);
    void get_history();

    bool operator==(const Account &other) const
    {
        return this->email == other.email;
    }
};

#endif