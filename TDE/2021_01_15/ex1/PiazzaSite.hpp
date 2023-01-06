#ifndef PIAZZASITE_HPP
#define PIAZZASITE_HPP
#include <string>
#include <set>
#include <unordered_map>
#include <vector>
#include "Instructor.hpp"
#include<iostream>
#include "Post.hpp"
#include "Student.hpp"
struct StudentViews
{
    std::string stud_login;
    unsigned views;
    StudentViews(const std::string stud_login, unsigned views);
};
bool operator<(const StudentViews &view1, const StudentViews &view2) {
        return (view1.views < view2.views)
               or ( (view1.views == view2.views ) and
                    (view1.stud_login < view2.stud_login ));
}


class PiazzaSite{
private:
    std::string code;
    Instructor instr;
    std::unordered_map<std::string, Student> studs;
    std::set<StudentViews> stud_views;
    std::vector<Post> posts;
public:
    PiazzaSite(const std::string &c, const Instructor &i):code(c), instr(i){};

    void register_student(const std::string &stud_login, const std::string &stud_pwd){
        Student stuart(stud_login, stud_pwd);
        studs.insert(std::make_pair(stud_login, stuart)); //O(1)
        StudentViews stuarts(stud_login, 0);
        stud_views.insert(stuarts); //O(logN)
    };

    void add_post(const std::string &stud_login, const std::string &date, const std::string &content){
        posts.emplace_back(date, content); //O(1)
        instr.add_unread_post(posts.size()); //O(1)
    };

    void add_answer(size_t post_id, const std::string &answer);

    void read_post_student(const std::string &stud_login, size_t post_id){
        if (studs.find(stud_login) == studs.end()) //O(1)
            std::cerr << "Non esiste student" << std::endl;
        else if (post_id > posts.size())
            std::cerr << "Non esiste post" << std::endl;
        else {
            unsigned views = studs.at(stud_login).get_views(); //O(1)
            StudentViews old_views(stud_login, views);
            StudentViews new_views(stud_login, ++views);
            stud_views.erase(old_views); //O(logN)
            stud_views.insert(new_views); //O(logN)
            studs.at(stud_login).inc_views(); //O(1)
            posts.at(post_id-1).inc_views(); //O(1)
        }
    };

    void read_post_instructor(size_t post_id){
        if (post_id > posts.size())
            std::cerr << "Non esiste post" << std::endl;
        else {
            instr.read_post(post_id); //O(1)
            posts.at(post_id-1).inc_views(); //O(1)
        }
    };

    void top_k_students(unsigned k) const{
        auto last = stud_views.rbegin();
        for (auto begin = last; begin != last + k; begin++){ ///O(k)*O(1)
            std::cout << begin->stud_login << " ";
        }
        std::cout << std::endl;
    };
};

#endif //PIAZZASITE_HPP