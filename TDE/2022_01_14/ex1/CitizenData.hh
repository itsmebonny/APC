#ifndef CITIZENDATA_H
#define CITIZENDATA_H
#include<string>
struct Date
{
    std::string date;
    std::string time;
    Date(std::string d, std::string t):date(d), time(t){};
};

class CitizenData
{
private:
    std::string healthNumber;
    std::string mobilePhoneNumber;
    std::string name;
    std::string lastName;
    std::string address;
    Date birthDate;
    unsigned numberOfShots;
    Date lastVaccineDate;
    Date nextVaccineDateLB;
public: 
    std::string get_LB() const;
    std::string get_phone() const;

    CitizenData();
    CitizenData(const std::string &healthNumber,
            const std::string &mobilePhoneNumber,
            const std::string &name, const std::string &lastName,
            const std::string &address, const Date &birthDate);
};



#endif //CITIZENDATA_H