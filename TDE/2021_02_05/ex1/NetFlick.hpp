#ifndef NETFLICK_HPP
#define NETFLICK_HPP
#include"User.hpp"
#include <set>
#include <unordered_map>
#include"Movie.hpp"
#include<iostream>
#include<cmath>
class NetFlick
{
private:
    std::vector<User> users;
    std::vector<Movie> movies;

    std::unordered_map<size_t, std::unordered_map<size_t, unsigned short>> ratings;
    std::vector<std::vector<size_t>> similarity_matrix;

    std::set<size_t> intersect_movies(size_t user_index1 , size_t user_index2) const;
    static const unsigned short max_rate = 5;
public:
    void add_user (const std::string & name){
        users.emplace_back(name);
    };
    void add_movie(const std::string & title, const std::string & cast){
        movies.emplace_back(movies, cast);
    };
    void add_rating(size_t user_index, size_t movie_index, unsigned short rate){
        std::unordered_map<size_t, unsigned short> rats;
        ratings.at(user_index).at(movie_index) = rate;
    };
    void compute_similarity_matrix(){
        similarity_matrix.resize(users.size(), std::vector<size_t>(users.size()));
        for (size_t i = 0; i < users.size(); i++)
        {
            for (size_t j = 0; j < users.size(); j++)
            {
                std::set<size_t> set_movies =  intersect_movies(i, j);
                for (auto begin = set_movies.begin(); begin != set_movies.end(); begin++)
                {
                    similarity_matrix.at(i).at(j) += max_rate - std::abs(ratings.at(i).at(*begin) - ratings.at(j).at(*begin));
                }
            }
        }
    };
    void movies_similar(size_t user_index, float min_rate) const{
        for (auto i = 0; i < similarity_matrix[user_index].size(); i++)
        {
            if(similarity_matrix[user_index][i] >= min_rate){
            for (auto begin = intersect_movies(i, i).begin(); begin != intersect_movies(i, i).end(); begin++){
                    std::cout << movies[*begin].get_title() << std::endl;
                }
                    
            }
        }
        
    };
};

#endif //NETFLICK_HPP