#ifndef POSTALOFFICE_H
#define POSTALOFFICE_H
#include<iostream>
#include<queue>
#include<map>
#include<string>
struct Date{
    std::string day;
    std::string time;
    Date(std::string day, std::string time):day(day), time(time){};
    bool operator<( Date &rhs){
        return (day < rhs.day) || (day == rhs.day && time < rhs.time);
    }
    bool operator==( Date &rhs){
        return (day == rhs.day && time == rhs.time);
    }
};
class PostalOffice
{
private:
    std::deque<std::string> queue;
    std::map<Date, std::string>bookingQueue;
    std::map<std::string, Date> appointments;
    size_t ticket_counter = 1, appts_counter = 1;
public:
    std::string enterQueue(){
        std::string ticket = "P" + std::to_string(ticket_counter);
        ticket_counter++;
        queue.push_back(ticket);
    };
    void resetCounter(){
        ticket_counter = 1; //to be executed at the end of the workday
    }

    void enterSystem(std::string bookingCode){
        bookingQueue.insert(std::make_pair(appointments[bookingCode], bookingCode));
        appointments.erase(bookingCode);
    };
    std::string ReserveTicket(std::map<std::string, Date> &m) const{
        return "R" + std::to_string(m.size()+1);
    }
    std::string addAppointment(std::string day, std::string time){
        Date d(day, time); 
        for(auto j : appointments){
            if (j.second == d){
                std::cerr << "Already booked" << std::endl;
            }
        }
        std::string ticket = ReserveTicket(appointments);
        appointments.insert(std::make_pair(ticket, d));
        return ticket;
    };
    std::string pickNext(std::string day, std::string time){
        Date d(day,time);
        std::string res;
        if(bookingQueue.find(d) == bookingQueue.end()){
            res = queue.front();
            queue.pop_front();
            return res;
        }
        else{
            res = bookingQueue[d];
            bookingQueue.erase(d);
            return res;
        }
    };

    
};

#endif //POSTALOFFICE_H