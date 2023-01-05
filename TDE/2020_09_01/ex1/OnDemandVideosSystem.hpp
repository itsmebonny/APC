#ifndef ONDEMANDVIDEOSSYSTEM_HPP
#define ONDEMANDVIDEOSSYSTEM_HPP

#include "Movie.hpp"
#include<map>
#include<set>
class OnDemandVideosSystem
{
private:
    std::map<std::string, Movie> streaming;
public:
    OnDemandVideosSystem();


    std::set<std::string> computeKeywords(const std::string &s) const ;
    std::set<std::string> splitWords(const std::string &s, char d = ' ') const ;
    std::set<std::string> setIntersect(const std::set<std::string> &set1, const std::set<std::string> &set2) const;
    std::set<std::string> setUnion(const std::set<std::string> &set1, const std::set<std::string> &set2) const;


    void addMovie(const std::string &p_title, const std::string &p_director, const std::vector<std::string> &p_actors, const std::string &p_genre){
        Movie m(p_title, p_director, p_actors, p_genre);
        streaming.insert(std::make_pair(p_title, m));
    }
    void searchMovie(const std::string &search_title) const {
        auto pos = streaming.find(search_title);
        if(pos != streaming.end())
            pos->second.print();
        else 
            std::cerr << "Non esiste" << std::endl;
    }
    void searchMovie(const std::string &search_string, const std::string &criterion) const {
        std::set<std::string> search = computeKeywords(search_string);
        std::vector<std::string> titles_found;
        if (criterion != "AND" && criterion != "OR")
            std::cerr << "Wrong criterion";
        else{
            std::map<std::string, std::set<std::string>> all_titles;
            for (auto i : streaming)
            {
                all_titles.insert(std::make_pair(i.first, splitWords(i.first)));
            }
            if(criterion == "AND"){
                for(auto i : all_titles){
                    if (setIntersect(i.second, search).size() == search.size())
                        titles_found.push_back(i.first);
                }
            }
            else{
                for(auto i : all_titles){
                    if (setIntersect(i.second, search).size() < search.size() && setIntersect(i.second, search).size() > 0)
                        titles_found.push_back(i.first);
                }
            }
        }
        for(auto i:titles_found)
            std::cout << i << std::endl;
    }
};
#endif //ONDEMANDVIDEOSSYSTEM_HPP