#ifndef MOVIE_HPP
#define MOVIE_HPP
#include<string>

class Movie
{
private:
    std::string title;
    std::string cast;
public:
    Movie(const std::string & t, const std::string & c):title(t), cast(c){};
    std::string get_title() const;
    std::string get_cast() const;
    void print();
};

#endif //MOVIE_HPP