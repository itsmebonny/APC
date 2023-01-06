#ifndef POST_HPP
#define POST_HPP
#include<vector>
#include<string>
class Post
{
private:
    static size_t auto_id;
    size_t id;
    std::string date;
    std::string content;
    std::vector<std::string> answers;
    size_t n_views;
public:
    Post(const std::string &d, const std::string &c):date(d), content(c){};
    void add_answer(const std::string &answer);
    size_t get_id() const;
    void inc_views(){n_views++;}
};

#endif //POST_HPP