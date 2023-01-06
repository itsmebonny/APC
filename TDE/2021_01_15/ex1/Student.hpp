#ifndef STUDENT_HPP
#define STUDENT_HPP
#include<string>
#include<vector>
class Student
{
private:
    std::string login;
    std::string pwd;
    std::vector<size_t> posts_created;
    size_t views;
public:
    Student();
    Student(const std::string &l, const std::string &p):login(l), pwd(p){};
    void create_post(size_t post_id);
    size_t get_views() const;
    void inc_views(){views++;};
    ~Student();
};

#endif //STUDENT_HPP
