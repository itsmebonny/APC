#ifndef REVIEW_H
#define REVIEW_H
#include<iostream>
#include<string>
#include<vector>
class Review
{
private:
    std::string title;
    std::string text;
    int rating;
public:
    Review(std::string t, std::string txt, int r):title(t), text(txt), rating(r){};
    std::string get_title(void){return title;}
    std::string get_text(void){return text;}
    int get_review(void){return rating;}
    void print_review(void){
        std::cout << title << std::endl;
        std::cout << text << std::endl;
        std::cout << rating << std::endl;
    }
    bool operator< (const Review rhs) const{
        return this->title < rhs.title;
    }
};


#endif //REVIEW_H