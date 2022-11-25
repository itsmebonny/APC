#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <string>
#include<iostream>

class Employee
{
private:
    std::string name;
    std::string surname; 
    unsigned employee_id;
protected:
    unsigned pay_rate;
    unsigned work_hours;
public:
    Employee(std::string n,std::string s,unsigned id):name(n), surname(s), employee_id(id){};
    ~Employee();

    void print(){
        std::cout << name << " " << surname << " " << employee_id << std::endl;
    }
    void set_work_hours(unsigned n){
        work_hours = n;
    }
    virtual double salary_cal() const = 0;
};

Employee::~Employee()
{
}

#endif EMPLOYEE_H