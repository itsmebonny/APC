#ifndef CALENDAR_H
#define  CALENDAR_H

#include <iostream>
#include <vector>

#include "Event.h"

class Calendar {

private:
    std::vector<Event> events;

public:
    Calendar(){};
    Calendar(std::vector<Event> ev);
    Calendar(Calendar &c);

    void addEvent (const Event&);
    void updateEvent (time_t, const std::string&, time_t, const std::string&);
    void print (void) const;
};

#endif // CALENDAR_H