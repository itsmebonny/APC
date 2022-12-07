// DataFrame.cpp source file

#include <iomanip>
#include "DataFrame.h"

std::string DataFrame::PREFIX1{"df1_"};
std::string DataFrame::PREFIX2{"df2_"};


// Helper functions Protos:
void tabbed(double value, bool showZeros = true);
void tabbed(std::string string);
void tab();
std::vector<std::string> addPrefix(const std::vector<std::string> & to, std::string prefix);




DataFrame::DataFrame(const std::string &columnNamesString) : DataFrame() {
    Keys columnsNames = split(columnNamesString, ' ');

    for (const Key &name: columnsNames)
        dataFrameData[name];
}


DataFrame::Keys DataFrame::split(const std::string &s, char delim) const {
    Key word;
    Keys v;
    std::istringstream columns(s);

    while (std::getline(columns, word, delim)) v.push_back(word);

    return v;
}

bool DataFrame::checkColumnName(const std::string &columnName) const {
    return dataFrameData.find(columnName) != dataFrameData.end();
}


Column DataFrame::getColumn(const std::string &columnName) const {
    if (checkColumnName(columnName))
        return dataFrameData.at(columnName);
    else {
        std::cerr << "Error, " << columnName << " is unknown" << std::endl;
        return Column();
    }
}


void DataFrame::setColumn(const std::string &columnName,
                           const Column &column) {
    if (checkColumnName(columnName))
        dataFrameData[columnName] = column;
    else
        std::cerr << "Error, " << columnName << " is unknown" << std::endl;
}



bool DataFrame::addColumn(const Key &columnName,
                           const Column &columnData) {
    if (!checkColumnName(columnName)) {
        dataFrameData[columnName] = columnData;
        return true;
    }
    else {
        return false;
    }
}



std::vector<DataFrame::Key> DataFrame::getColumnNames() const {

    Keys names = Keys();

    for (const valueType &element: dataFrameData) {
        std::string s = element.first;
        names.push_back(s);
    }

    return names;
}


// // we se are simulating arrays, number or rows will be the max value in keys
dimension DataFrame::getDimension() const {
    auto colNames = getColumnNames();
    if (colNames.empty()){
        return {0,0};
    }

    auto cols = colNames.size();

    // cannot be equal, se we have sparse columns:

    /* if dense, every column with same height, so:
    auto values0 = get_column(colNames[0]);
    auto rows = values0.height();
     */
    
    // but we must search for max key:
    size_t rows = 0;
    for(std::string name: colNames){
        auto values = getColumn(name);
        auto H = values.height();
        rows = std::max(rows, H);
    }
    
    return {rows, cols};
}



void DataFrame::print(void) const {

    // write all columns names:
    auto colNames = getColumnNames();
    for (auto t: colNames) {
        tabbed(t);
    }

    newLine();

    auto dimension = getDimension();
    
    if (dimension.rows == 0)
        return;

    for (int row = 0; row < dimension.rows; row++) {

        auto valuesArray = getValuesAtRow(row);
            for(auto v : valuesArray){
                tabbed(v);
            }
            newLine();
    }

    newLine();
}


// TO BE IMPLEMENTED:

DataFrame
DataFrame::hstack(DataFrame &otherDataFrame){
    DataFrame CorniceDati;
    
    auto begin = this->dataFrameData.begin();
    size_t i = 0;
    std::vector<Key> key = addPrefix(this->getColumnNames(), PREFIX1);
    while(begin != this->dataFrameData.end())
    {
        CorniceDati.addColumn(key.at(i), begin->second);
        begin++;
        i++;
    }
    unsigned columns = otherDataFrame.getDimension().cols;
    
    for(size_t i = 0; i < columns; i++)
    {
        CorniceDati.addColumn(addPrefix(otherDataFrame.getColumnNames(), PREFIX2).at(i), otherDataFrame.getColumn(otherDataFrame.getColumnNames().at(i)));
    }
    
    return CorniceDati;

}

DataFrame DataFrame::join(DataFrame &otherDataFrame, std::string onMyCol, std::string onColOfOther){
    DataFrame CorniceDatiSQL, c1, c2;
    Column colonna1 = this->getColumn(onMyCol), colonna2 = otherDataFrame.getColumn(onColOfOther), colonnina, colonnona;
    if(colonna1.height() > colonna2.height()){
        colonnina = colonna2;
        colonnona = colonna1;
    }
    else{
        colonnona = colonna2;
        colonnina = colonna1;
    }
    int found = 0;
    unsigned num_swap = 0;
    colonnina.print(onMyCol);
    colonnona.print(onColOfOther);
    for (size_t i = 0; i < colonnona.height(); i++)
    {
        std::cout << "Looking for: "<< colonnona.values.at(i) << std::endl;
        if (colonnina.values.find(colonnona.values.at(i)) != colonnina.values.end())
        {   
            auto begin = this->dataFrameData.begin();
            auto begin2 = otherDataFrame.dataFrameData.begin();
            while (begin != this->dataFrameData.end())
            {   
                if (i > colonnina.height())
                    found = 0;
                else
                    found = i;
                
                begin->second.insert(begin->second.values.at(found), num_swap);
                begin++;
            }
            while (begin2 != otherDataFrame.dataFrameData.end())
            {   
                if (i > colonnona.height())
                    found = 0;
                else
                    found = i;
                begin2->second.insert(begin2->second.values.at(found), num_swap);
                begin2++;
            }
            num_swap++;
            
        }
        
    }
    
    for (size_t i = num_swap; i < colonnina.height(); i++)
    {
        this->erase_row(i);
    }
        for (size_t i = num_swap; i < colonnona.height(); i++)
    {
        otherDataFrame.erase_row(i);
    }
    CorniceDatiSQL = this->hstack(otherDataFrame);
    return CorniceDatiSQL;
}

void DataFrame::erase_row(size_t n){
    auto begin = this->dataFrameData.begin();
    while (begin != this->dataFrameData.end())
    {
        begin->second.erase_item(n);
        begin++;
    }
    
    
}
// ancillary code

DataFrame::DataFrame(std::vector<std::string> columnsNames)
: DataFrame() {
    for (const Key &name: columnsNames)
        dataFrameData[name];
}


ValuesArray DataFrame::getValuesAtRow(size_t row) const{
    ValuesArray result = {};
    
    auto colNames = getColumnNames();
    for (auto name:colNames) {
        auto column = getColumn(name);
        auto value = column.values[row];
        result.push_back(value);
    }
    return result;
}




// MARK: Helper functions:



void tabbed(double value, bool showZeros){

    if (value == 0 && !showZeros){
        std::cout << "       " << "|";
    }else{
        std::cout << std::setw(7);
        std::cout << value << "|";
    }
}



void tabbed(std::string string){
    auto stdLen = 7;
    auto len = string.size();
    auto spaces = stdLen-len;
    std::cout << string;
    for (int i = 0; i < spaces; ++i) {
        std::cout << " ";
    }
    std::cout << "|";

}

void tab(){
    tabbed("");
}

void newLine(std::string s){
    std::cout << s << std::endl;
}



std::vector<std::string> addPrefix(const std::vector<std::string> & to, std::string prefix){
    std::vector<std::string> out;

    std::transform(to.begin(), to.end(),
                   std::back_inserter(out),
                   [&prefix](std::string v) { return prefix+v; }
    );
    return out;
}