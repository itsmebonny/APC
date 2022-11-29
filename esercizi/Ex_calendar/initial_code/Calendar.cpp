#include "Calendar.h"

Calendar::Calendar(std::vector<Event> ev):events(ev){}
Calendar::Calendar(Calendar &c):events(c.events){}

void Calendar::addEvent(const Event& e){
    events.push_back(e);
}
void Calendar::updateEvent (time_t t0, const std::string& n0, time_t t1, const std::string& n1){
    for (size_t i = 0; i < events.size(); i++)
    {
        if (events[i].getName() == n0 && events[i].getTime() == t0)
        {
            events[i].setName(n1);
            events[i].setTime(t1);
        }
        
    }
}
void Calendar::print()const{
    for (size_t i = 0; i < events.size(); i++)
    {
        std::cout << events[i].getTime() << " " << events[i].getName() << " ";
    }
    std::cout << std::endl;
    
}
