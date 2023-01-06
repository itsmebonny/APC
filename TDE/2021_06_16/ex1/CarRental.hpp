#ifndef CARRENTAL_HPP
#define CARRENTAL_HPP
#include "Transfer.hpp"
class CarRental:public Transfer
{
private:
    std::string pick_up_date;
    std::string drop_off_date;
    std::string agency_address;
    unsigned short n_days;
public:
    CarRental(const std::string &description, float cost,
        const std::string &pick_up_date, const std::string &drop_off_date,
        const std::string &agency_address, const unsigned short n_days ):Transfer(description, cost), pick_up_date(pick_up_date), drop_off_date(drop_off_date), agency_address(agency_address), n_days(n_days){};
    float get_cost() const{
        return cost;
    };
};





#endif //CARRENTAL_HPP