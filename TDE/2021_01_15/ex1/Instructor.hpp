#ifndef INSTRUCTOR_HPP
#define INSTRUCTOR_HPP
#include<string>
#include<unordered_set>
#include<algorithm>
class Instructor
{
private:
    std::string login;
    std::string pwd;
    std::unordered_set<size_t> post_unread;
public:
    Instructor(const std::string &login, const std::string &pwd);
    void add_unread_post (size_t post_id){
        post_unread.insert(post_id); //O(1)
    };
    void read_post(size_t post_id){
        post_unread.erase(post_id); //O(1)
    };
};

#endif //INSTRUCTOR_HPP