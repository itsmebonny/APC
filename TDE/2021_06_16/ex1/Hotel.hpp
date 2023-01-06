#ifndef HOTEL_HPP
#define HOTEL_HPP
#include<string>
class Hotel
{
private:
    std::string name;
    std::string city;
    std::string address;
    unsigned short rooms_number;
    float cost_per_night;
public:
    Hotel(const std::string & name,
        const std::string & city,
        const std::string & address,
        unsigned short rooms_number,
        float cost_per_night):name(name), city(city), address(address), rooms_number(rooms_number), cost_per_night(cost_per_night){};
    float get_cost_per_night() const;
    std::string to_string() const;
};


#endif //HOTEL_HPP