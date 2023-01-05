#ifndef GOODREADS_H
#define GOODREADS_H
#include<map>
#include<set>
#include"Review.hpp"
#include"Book.hpp"
#include<algorithm>
class GoodReads
{
private:
    std::map<std::string, Book> books;
    std::map<std::string, std::set<Review>> goodreads;
public:
    void add_book(std::string title, std::string author, std::string publisher, unsigned pages){
        Book b(title, author, publisher, pages);
        std::set<Review> r;
        books.insert(std::make_pair(title, b));
        goodreads.insert(std::make_pair(title, r));
    }
    void add_review(const std::string title, const std::string text, const int rating){
        const Review r(title, text, rating);
        auto pos = goodreads.find(title);
        pos->second.insert(r);
    }
    std::vector<std::string> split(const std::string &s, char d);
    float set_avg(std::set<Review> &review){
        float sum = 0;
        int count = 0;
        for (auto i : review){
            sum += i.get_review();
            count++;
        }
        return sum/count;
    }
    float get_avg_rating(const std::string & title){
        auto pos = goodreads.find(title);
        return set_avg(pos->second);
    }
    float get_avg_rating(){
        float sum = 0;
        int count = 0;
        for (auto i : goodreads){
            sum += set_avg(i.second);
            count++;
        }
        return sum/count;
    }
    void search_reviews(const std::vector<std::string> & keywords){
        std::set checkkey(keywords.begin(), keywords.end());
        for(auto i:goodreads){
            for(auto j:i.second){
                std::vector<std::string> checkv = split(j.get_text(), ' ');
                std::set check(checkv.begin(), checkv.end());
                if (std::includes(check.cbegin(), check.cend(), checkkey.cbegin(), checkkey.cend()))
                    j.print_review();
                
            }
        }
        
    }
    void print_book(const std::string & title){
        auto pos = goodreads.find(title);
    }
    GoodReads() = default;
};

#endif //GOODREADS_H