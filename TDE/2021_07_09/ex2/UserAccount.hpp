#ifndef USERACCOUNT_H
#define USERACCOUNT_H
#include<string>
#include"Cart.hpp"
class UserAccount
{
private:
    std::string email_login;
    std::string password;
    std::string address;
    std::string mobile_phone;
    Cart shopping_cart;
public:
    UserAccount(const std::string &email_login,
            const std::string &password, const std::string &address,
            const std::string &mobile_phone):email_login(email_login), password(password), address(address), mobile_phone(mobile_phone){};
    UserAccount(const std::string &email_login);
    void add_to_cart(unsigned product_id, float price);
};


#endif //USERACCOUNT_H