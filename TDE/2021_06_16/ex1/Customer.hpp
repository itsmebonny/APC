#ifndef CUSTOMER_HPP
#define CUSTOMER_HPP
#include<string>

class Customer
{
private:
    std::string name;
    std::string birthday;
    char gender;
public:
    Customer(const std::string & name,
            const std::string & birthday,
            char gender):name(name), birthday(birthday), gender(gender){};
    std::string to_string() const;
};


#endif //CUSTOMER_HPP