#ifndef MOVIES_HPP
#define MOVIES_HPP
#include<string>
#include<vector>
#include<iostream>

class Movie
{
private:
    std::string title;
    std::string director;
    std::vector<std::string> actors;
    std::string genre;
public:
    Movie() = default;
    Movie(std::string t, std::string d, std::vector<std::string> a, std::string g):title(t), director(d), actors(a), genre(g){}
    std::string get_title(){return title;}
    std::string get_director(){return director;}
    std::vector<std::string> get_actors(){return actors;}
    std::string get_genre(){return genre;}
    void print() const {
        std::cout << title << std::endl;
        std::cout << director << std::endl;
        for (auto i : actors)
            std::cout << i << " ";
            std::cout << std::endl;
        std::cout << genre << std::endl;
    }
};


#endif //MOVIES_HPP