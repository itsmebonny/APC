#ifndef DATAFRAME_HH
#define DATAFRAME_HH
#include<string>
#include<map>
#include<vector>
#include<stdexcept>
#include<set>
std::vector<std::string> split(const std::string & s, char d = ' ');
class DataFrame
{
private:
    std::map<std::string, std::vector<double>> df;
public:
    DataFrame(std::string s){
        std::vector<std::string> names = split(s);
        for (auto i : names){
            df[i] = {};
        }
    };
    void set_column(std::vector<double> v, std::string s){
        if(df.find(s) != df.end())
        {df.erase(s);
        df[s] = v;}
    }
    std::set<double> unique(std::string s) const {
        if(df.find(s) != df.end()){
            std::set<double> res(df.find(s)->second.begin(), df.find(s)->second.end());
        return res;}
    }
    std::vector<double> get_values(std::string s) const {
        if(df.find(s) != df.end()){
            std::vector<double> res = df.at(s);
        return res;}
    } 
    std::vector<std::string> get_column_names() const {
        std::vector<std::string> res;
        for(auto i:df)
            res.push_back(i.first);
        return res;
    }
    void drop_column(std::string s){
        if(df.find(s) != df.end())
        df.erase(s);
    }
    size_t max_rows() const{
        size_t max = 0;
        for (auto i : df)
        {
            if (i.second.size() > max)
                max = i.second.size();
        }
        
    }
    DataFrame concatenate(const DataFrame second) const {
        DataFrame res = *this;
        for (auto i : second.get_column_names())
        {
            std::vector<double> column = this->df.at(i);
            column.insert(column.end(), second.get_values(i).begin(), second.get_values(i).end());
            res.set_column(column, i);
        }
        return res;
    }
    std::vector<double> sum_by_rows() const {
        std::vector<double> res(max_rows());
        for(auto j:df){
            for (size_t i = 0; i < res.size(); i++)
            {   try
                {res[i] += j.second.at(i);}
                catch(std::out_of_range)
                {
                    //do nothing
                }
            }
            
        }
        return res;
    }
};


#endif //DATAFRAME_HH