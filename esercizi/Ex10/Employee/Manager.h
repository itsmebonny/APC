#ifndef EMPLOYEE_MANAGER_H
#define EMPLOYEE_MANAGER_H
#include "Employee.h"
#include "Developer.h"

class Manager:public Developer{
    private:
        double m_hours = 0;
        const double m_rate = 15;
        const double wsh_hours = 20;
    public:
        Manager(std::string n, std::string s, unsigned id):Developer(n,s,id){};
    
    void set_m_hours(unsigned n){
        m_hours = n;
    }
    
    double salary_cal() const override {
        double m_pay = m_hours * m_rate;
        double w_pay = (wsh_hours - work_hours) * pay_rate;
        return (m_pay + w_pay);
    }

};




#endif EMPLOYEE_MANAGER_H