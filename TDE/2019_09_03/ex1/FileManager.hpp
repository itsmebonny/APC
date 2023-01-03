#ifndef FILEMANAGER_H
#define FILEMANAGER_H
#include<iostream>
#include<deque>
#include<algorithm>

class FileManager
{
private:
    std::size_t max_cache;
    std::string filename;
    std::deque<std::string> storage;
    void ReduceCache(std::size_t required_cache_size){
        std::size_t loc_cache = 0, tot_cache;
        for (size_t i = 0; i < storage.size(); i++)
        {
            loc_cache += GetFileSize(storage.at(i));
        }
        while (loc_cache > required_cache_size)
        {
            loc_cache -= GetFileSize(storage.at(0));
            storage.pop_front();
        }
    };
public:    
    FileManager(std::size_t max_cache_size);
    void SetMaxCacheSize(std::size_t new_max_cache_size){
        max_cache = new_max_cache_size;
        ReduceCache(max_cache);
        };
    void DownloadFile(const std::string & file_name){
        if (std::find(storage.begin(), storage.end(), file_name) != storage.end())
            storage.erase(std::find(storage.begin(), storage.end(), file_name));
        storage.push_back(file_name);
        ReduceCache(max_cache);
    };
    void AccessFile(const std::string & file_name){
        if (std::find(storage.begin(), storage.end(), file_name) != storage.end())
        {
            storage.erase(std::find(storage.begin(), storage.end(), file_name));
            storage.push_back(file_name);
        }
        ReduceCache(max_cache);
    };
    void RemoveFileFromCache(const std::string & file_name){
        if (std::find(storage.begin(), storage.end(), file_name) != storage.end())
            storage.erase(std::find(storage.begin(), storage.end(), file_name));
        ReduceCache(max_cache);
    };
    std::size_t GetFileSize(const std::string & file_name);
};


#endif //FILEMANAGER_H