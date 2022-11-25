#ifndef EMPLOYEE_SECRETARY_H
#define EMPLOYEE_SECRETARY_H

#include "Employee.h"

class Secretary:public Employee{
public:
    Secretary(std::string n, std::string s, unsigned id):Employee(n, s, id){};
    

    double salary_cal() const override{
        return work_hours * pay_rate;
    }
};





#endif EMPLOYEE_SECRETARY_H