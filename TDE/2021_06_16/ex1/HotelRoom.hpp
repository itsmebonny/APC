#ifndef HOTELROOM_HPP
#define HOTELROOM_HPP
#include "Product.hpp"
#include "Hotel.hpp"
class HotelRoom:public Product
{
private:
    std::string check_in_date;
    std::string check_out_date;
    std::string room_number;
    unsigned short nights_number;
    const Hotel* hotel;
public:
    HotelRoom(const std::string &description, const std::string &check_in_date,
            const std::string &checkOutDate, const std::string &room_number,
            unsigned short nights_number, const Hotel* hotel):Product(description), check_in_date(check_in_date), check_out_date(checkOutDate), nights_number(nights_number), hotel(hotel){};
    float get_cost() const{
        return hotel->get_cost_per_night()*nights_number;
    };
};


#endif //HOTELROOM_HPP