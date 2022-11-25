#ifndef EMPLOYEE_DEVELOPER_H   
#define EMPLOYEE_DEVELOPER_H   

#include "Employee.h"

class Developer:public Employee{
protected:
    unsigned wsh_hours = 0;
    const double wsh_rate = 8.0;
public:
    Developer(std::string n, std::string s, unsigned id):Employee(n,s,id){};
    
    double salary_cal() const override{
        double wsh_pay = wsh_hours * wsh_rate;
        return wsh_pay;
    }
    void set_wsh_hours(unsigned n){
        wsh_hours = n;
    }

};





#endif EMPLOYEE_DEVELOPER_H