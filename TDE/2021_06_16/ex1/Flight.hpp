#ifndef FLIGHT_HPP
#define FLIGHT_HPP
#include "Transfer.hpp"
class Flight:public Transfer
{
private:
    std::string departure;
    std::string destination;
    std::string date;
    std::string departing_time;
public:
    Flight(const std::string &description, float cost,
        const std::string &departure, const std::string &destination,
        const std::string &date, const std::string &departing_time ):Transfer(description, cost), departure(departure), destination(destination), date(date), departing_time(departing_time){};
    float get_cost() const{
        return cost;
    };};


#endif //FLIGHT_HPP