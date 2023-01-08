#ifndef VACCINATIONCENTERDATA_H
#define VACCINATIONCENTERDATA_H
#include"CitizenData.hh"
#include<map>
class VaccinationCenterData
{
private:
    std::string name;
    std::string address;
    std::string zipCode;
    std::map<Date,std::map<unsigned,unsigned>> availableSlots;
//availableSlots[date][hour] store the
//slots available at a given day and time
public:
    VaccinationCenterData();
    VaccinationCenterData(const std::string &name, const std::string &address,
const std::string &zipCode);
    void addSlot(const Date &date, unsigned hour,
unsigned nSlots){};
    bool checkAvailability (const Date &date, unsigned hour) const{
        return (availableSlots.find(date) != availableSlots.end() && availableSlots.at(date).find(hour) != availableSlots.at(date).end());
    };
    void reserveSlot(const Date &date, unsigned hour);
    void releaseSlot(const Date &date, unsigned hour);
};


#endif //VACCINATIONCENTERDATA_H