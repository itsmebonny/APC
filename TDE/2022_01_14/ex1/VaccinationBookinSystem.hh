#ifndef VACCINATIONBOOKINGSYSTEM_H
#define VACCINATIONBOOKINGSYSTEM_H
#include"CitizenData.hh"
#include"VaccinationCenterData.hh"
#include"ReservationData.hh"
#include"PreBookingData.hh"
#include"unordered_map"
class VaccinationBookinSystem
{
private:
    std::unordered_map<std::string, CitizenData> citizens; // given a CF provides its data
    std::unordered_map<std::string, VaccinationCenterData> vaccinationCenters; // given a vaccination center ID provides its data
    std::unordered_map<std::string, PreBookingData> preBookings; // associates a pre-boooking code with its data
    std::unordered_map<std::string, ReservationData> reservations; // associates a reservation code with its data
    std::unordered_map<std::string, std::string> citizensPrebookings; // associates a citizen CF with her/his pre-booking code
    std::unordered_map<std::string, std::string> citizensReservations; // associates a citizen CF with her/his reservation code
public:
    void addCitizen(const std::string &CF, const std::string &healthNumber,
const std::string &mobilePhoneNumber, const std::string &name,
const std::string &lastName, const std::string &address,
const Date &birthDate);
    void addVaccinationCenter(const std::string &ID, const std::string &name,
const std::string &address, const std::string &zipCode);    
    void addVaccinationCenterSlot(const std::string &ID, const Date &date,
unsigned hour, unsigned nSlots);    
    std::string preBooking(const std::string &citizenCF, const std::string &vaccinationCenterID,
const Date &date, unsigned hour){
    std::string res;
    if(citizens.find(citizenCF) != citizens.end() && vaccinationCenters.find(vaccinationCenterID) != vaccinationCenters.end() && citizensPrebookings.find(citizenCF) == citizensPrebookings.end() && citizensReservations.find(citizenCF) == citizensReservations.end() && citizens.find(citizenCF)->second.get_LB() < date.date && vaccinationCenters.find(vaccinationCenterID)->second.checkAvailability(date, hour)){
        PreBookingData p(citizens.at(citizenCF).get_phone(),citizenCF,vaccinationCenterID, date, hour);
        preBookings[p.get_booking_code()] = p;
        citizensPrebookings[citizenCF] = p.get_booking_code();
        vaccinationCenters.at(vaccinationCenterID).reserveSlot(date, hour);
        return p.get_booking_code();
    }
    else
        return res;
};    
    std::string reserve(const std::string &preBookingCode);    
    void moveReservation(const std::string &reservationCode,
const std::string &vaccinationCenterID,
const Date &newDate, unsigned newHour){
    if(reservations.find(reservationCode) != reservations.end() && newDate.date < citizens.at(reservations.at(reservationCode).get_cf()).get_LB() && vaccinationCenters.at(vaccinationCenterID).checkAvailability(newDate, newHour)){
        vaccinationCenters.at(vaccinationCenterID).releaseSlot(reservations.at(reservationCode).get_date(), reservations.at(reservationCode).get_hour());
        vaccinationCenters.at(vaccinationCenterID).reserveSlot(newDate, newHour);
    }
};    
};


#endif //VACCINATIONBOOKINGSYSTEM_H