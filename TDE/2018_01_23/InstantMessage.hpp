#ifndef INSTANMESSAGE_H
#define INSTANTMESSAGE_H

#include <iostream>
#include <string>
#include <map>

class InstantMessage
{
private:
    std::multimap<int, std::string> messages;
public:
    InstantMessage();
    InstantMessage(std::string s, int t){messages.insert(std::make_pair(t, s));};
    void send_message(int t, std::string s){
        messages.insert(std::make_pair(t, s));
    };
    std::multimap<int, std::string> search_by_time(int ts){
        std::multimap<int, std::string> recent;
        for (auto k : messages)
        {
            if(k.first >= ts)
                recent.insert(std::make_pair(k.first, k.second));
        }
    return recent;
    };
    std::multimap<int, std::string> search_by_word(std::string s){
        std::multimap<int, std::string> search_result;
        for (auto k : messages)
        {
            int pos = k.second.find(s, 0);
            if (pos <= k.second.length()){
                search_result.insert(std::make_pair(k.first, k.second));
            }
        }
        return search_result;
    };
};

#endif //INSTANTMESSAGE_H