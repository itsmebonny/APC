#include "Calendar.h"

Calendar::Calendar(std::vector<Event> ev):events(ev){}
Calendar::Calendar(Calendar &c):events(c.events){}

void Calendar::addEvent(const Event& e){
    events.push_back(e);
}
void Calendar::updateEvent (time_t, const std::string&, time_t, const std::string&){

}
void Calendar::print()const{

}
