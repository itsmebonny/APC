#ifndef TIMESERIES_H
#define TIMESERIES_H
#include<map>
#include<string>
#include<vector>
#include<limits>
#include<numeric>
class TimeSeries
{
private:
    std::map<std::string, std::map<std::string, float>> time_series;
public:
    TimeSeries();
    void add_registration(const std::string & date, const std::string & time, float value){
        time_series[date][time] = value;
    };
    float get_registration(const std::string & date, const std::string & time) const{
        if(time_series.find(date) != time_series.end() && time_series.at(date).find(time) != time_series.at(date).end())
            return time_series.at(date).at(time);
        else
            return std::numeric_limits<float>::quiet_NaN();
    };
    float get_registration_by_date(const std::string & date) const{
        float res;
        int count;
        for (auto i : time_series.at(date)){
            res += i.second;
            count++;
        }
        return res/count;
    };
    float get_registration_by_time(const std::string & time) const{
        float res = 0;
        int count = 0;
        for(auto i : time_series){
            if(i.second.find(time) != i.second.end()){
                res += i.second.at(time);
                count++;
            }
        }
        return res/count;
    };
    std::vector<float> get_registration_range(const std::string & date1, const std::string & time1, const std::string & date2) const{
        std::vector<float> res;
        auto pos_d1 = time_series.find(date1), pos_d2 = time_series.find(date2);
        auto pos_t1 = time_series.at(date1).find(time1);
        if (date2 < date1 && pos_d1 == time_series.end())
            return res;
        else{
            if(pos_d2 == time_series.end());
                for(auto i = time_series.end(); i != pos_d1; i--){
                    if (i->first < date2)
                        pos_d2 = i;
                }
            if (pos_t1 == time_series.at(date1).end())
            {
                for(auto i = time_series.at(date1).begin(); i != time_series.at(date1).end(); i++){
                    if (i->first > time1)
                        pos_t1 = i;
                }
            }
            for (auto j = pos_t1; j != time_series.at(date1).end(); j++)
            {
                res.push_back(j->second);
            }
            for (auto i = ++pos_d1; i != pos_d2; i++)
            {
                for (auto j : i->second)
                {
                    res.push_back(j.second);
                }
            }
            }
            return res;
        };
    TimeSeries intersect_time_series(const TimeSeries & ts) const{
        TimeSeries res;
        for (auto i : this->time_series)
        {
            for (auto j : i.second)
            {
                if(ts.get_registration(i.first, j.first) != std::numeric_limits<float>::quiet_NaN())
                    res.add_registration(i.first, j.first, (j.second+ts.get_registration(i.first, j.first))/2);
            }   
        }
        return res;
    };
};
#endif //TIMESERIES_H