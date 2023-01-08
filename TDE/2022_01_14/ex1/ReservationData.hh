#ifndef RESERVATIONDATA_H
#define RESERVATIONDATA_H
#include"CitizenData.hh"
class ReservationData
{
private:
    static unsigned counter;
    std::string citizenPhoneNumber;
    std::string citizenCF;
    std::string vaccinationCenterID;
    Date date;
    unsigned hour;
    std::string reservationCode;
    std::string preBookingCode;
public:
    ReservationData();
    ReservationData(const std::string &citizenPhoneNumber,
                const std::string &citizenCf,
                const std::string &vaccinationCenterId,
                const Date &date, unsigned hour,
                const std::string &preBookingCode);
    std::string get_cf();
    Date get_date();
    unsigned get_hour();
};

#endif //RESERVATIONDATA_H