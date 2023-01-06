 #ifndef TRAVELAGENCY_HPP
#define TRAVELAGENCY_HPP
#include"Customer.hpp"
#include"Flight.hpp"
#include"Hotel.hpp"
#include <vector>
#include <map>
#include "Travel.hpp"
#include<iostream>
#include"HotelRoom.hpp"
class TravelAgency
{
private:
    std::vector<Customer> customers;
    std::vector<Hotel> hotels;
    std::vector<Travel> travels;
    std::multimap<std::string, size_t> search_hotel_location; // hotel_city, hotel_index
public:
    void add_customer(const std::string &name, const std::string &birthday, char gender);
    void add_travel(const std::string &depart_date, const std::string &return_date,
                    const std::string &destination);
    void add_customer_to_travel(size_t travel_index, size_t customer_index);
    void add_hotel(const std::string &name, const std::string &city,
                const std::string &address, unsigned short rooms_number, float cost_per_night){
                    hotels.emplace_back(name, city, address, rooms_number, cost_per_night);
                    search_hotel_location.insert(std::make_pair(city, hotels.size()-1));
                };
    void add_car_rental_to_travel(size_t travel_index, float cost,
                                const std::string &pickup_date, const std::string &drop_off_date,
                                const std::string &agency_address, unsigned short n_days);
    void add_flight_to_travel(size_t travel_index,float cost, const std::string &departure,
                            const std::string &destination, const std::string &date, const std::string &departing_time){
                                std::shared_ptr<Flight>f_sp =  std::make_shared<Flight>("flight", cost, departure, destination, date, departing_time);
                                travels.at(travel_index).add_product(f_sp);
                            };
    void add_hotel_room_to_travel(size_t travel_index, const std::string &check_in_date,
                                const std::string &check_out_date, const std::string &room_number,
                                unsigned short nights_number, size_t hotel_index){
                                std::shared_ptr<HotelRoom>hr_sp =  std::make_shared<HotelRoom>("Room", check_in_date, check_out_date, room_number, nights_number, hotel_index);
                                travels.at(travel_index).add_product(hr_sp);
                                }
    void search_hotel(std::string city) const{
        auto range = search_hotel_location.equal_range(city);
        
        for (auto begin = range.first; begin != range.second; begin++){
            std::cout << hotels[begin->second].to_string() << std::endl;
        }
    };
};


#endif //TRAVELAGENCY_HPP