#ifndef ECOMMERCE_H
#define ECOMMERCE_H
#include<vector>
#include<string>
#include<map>
#include"UserAccount.hpp"
#include"ProductData.hpp"
class ECommerce
{
private:
    std::map<std::string, UserAccount> users;
    std::map<unsigned, ProductData> products;
public:
    ECommerce();
    void add_user(const std::string &email_login, const std::string &pwd, const std::string &address,
                const std::string &mobile_phone){
                    UserAccount U(email_login, pwd, address, mobile_phone);
                    users.insert(std::make_pair(email_login, U));
                };
    void add_product(unsigned id, const std::string &description, float price,
    const std::vector<unsigned> &similar_products_id){
        ProductData P(description, price, similar_products_id);
        products.insert(std::make_pair(id, P));
    };
    void add_to_cart(const std::string &user_email, unsigned product_id){
        users.at(user_email).add_to_cart(product_id, products[product_id].get_price());
    };
};

#endif //ECOMMERCE_H