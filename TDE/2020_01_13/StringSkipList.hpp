#ifndef STRINGSKIPLIST_H
#define STRINGSKIPLIST_H
#include <iostream>
#include <string>
#include <list>
#include <cmath>
#include <algorithm>

class StringSkipList
{
private:
    std::list<std::string> normal_lane;
    std::list<std::list<std::string>::iterator> express_lane;
public:
    StringSkipList() = default;
    void consolidate(void){
        express_lane.clear();
        express_lane.insert(express_lane.begin(), normal_lane.begin());
        int root_size = std::floor(std::sqrt(normal_lane.size())), count = 0;
        for(auto i = normal_lane.begin(); i != normal_lane.end(); i++)
            {if (count > root_size){
                count = 0;
                express_lane.insert(express_lane.end(), i);}
            count++;}
        express_lane.insert(express_lane.end(), --normal_lane.end());

    };
    StringSkipList(std::list<std::string> s):normal_lane(s){
        this->consolidate();
    };
    std::list<std::string>::iterator end(){
        return ++normal_lane.end();
    }
    std::list<std::string>::iterator find(const std::string &s){
        for(auto i = express_lane.begin(); i != express_lane.end(); i++)
        {
            if (**i == s)
                return *i;
            else if (**i > s){
                i--;
                for (auto begin = *i; begin != normal_lane.end(); begin++){
                    if (*begin == s)
                    {
                        return begin;
                    }
                } 
                    return this->end();
                }
            
            else{
                for (auto begin = normal_lane.begin(); begin != normal_lane.end(); begin++){
                    if (*begin == s)
                    {
                        return begin;
                    } 
                }
                return this->end();
        }}
    };
    void insert(const std::string &s){
       for(auto i = express_lane.begin(); i != express_lane.end(); i++)
        {
           
            if (**i > s){
                i--;
                for (auto begin = *i; begin != normal_lane.end(); begin++){
                    if (*begin > s)
                    {
                        begin--;
                        normal_lane.insert(begin, s);
                    }
                } 
                    normal_lane.push_back(s);
                }
            
            else{
                normal_lane.push_back(s);
        }}
    };
    void print(void){
        std::cout << "Normal Lane: ";
        for (auto i : normal_lane)
            std::cout << i << " ";
        std::cout << std::endl;
        std::cout << "Express Lane: ";
        for (auto i : express_lane)
            std::cout << *i << " ";
        std::cout << std::endl;

    };
};
#endif //STRINGSKIPLIST_H