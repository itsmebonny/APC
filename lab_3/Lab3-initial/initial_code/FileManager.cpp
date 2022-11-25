#include <iostream>
#include <fstream>
#include <sstream>

#include "FileManager.h"




// reads the file passed as argument, whose elements are separated by
// the given character, and returns a table with the corresponding fields
const FileManager::table_type &FileManager::parse_file (const std::string& filename, char d){
    std::ifstream f(filename);
    std::string line;
    unsigned i = 0;
    unsigned j = 0;
    while (std::getline(f, line))
    {
        std::istringstream record(line);
        std::string stringa;
        fields.push_back(row_type());
        while (std::getline(record, stringa, ','))
        {
            while (fields[i].size() == 4)
            {
                i++;
            }
            
            fields[i].push_back(stringa);
            j++;
            
        }
        i++;    
    }
    
    return fields;
}


