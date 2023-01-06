#ifndef USER_HPP
#define USER_HPP
#include<string>
#include<vector>

class User
{
private:
    std::string name;
    std::vector<size_t> movie_indexes;
public:
    User(const std::string & n):name(n){}
    const std::vector<size_t>& get_movies_indexes() const;
    void add_movie_index(size_t movie_index);
};

#endif //USER_HPP