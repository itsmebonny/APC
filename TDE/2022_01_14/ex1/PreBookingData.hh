#ifndef PREBOOKINGDATA_H
#define PREBOOKINGDATA_H
#include"CitizenData.hh"
class PreBookingData
{
private:
    static unsigned counter;
    std::string citizenPhoneNumber;
    std::string citizenCF;
    std::string vaccinationCenterID;
    Date date;
    unsigned hour;
    std::string bookingCode;

public:
    PreBookingData();
    PreBookingData(const std::string &citizenPhoneNumber,
                const std::string &citizenCf,
                const std::string &vaccinationCenterId,
                const Date &date, unsigned hour);
    std::string get_booking_code();
};
#endif //PREBOOKINGDATA_H