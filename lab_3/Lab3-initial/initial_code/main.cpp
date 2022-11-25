#include <iostream>
#include <unordered_map>

#include "FileManager.h"

using std::unordered_map;
using std::vector;
using std::string;
using std::cout;
using std::endl;
using std::cerr;

typedef vector<string> row_type;
typedef vector<row_type> table_type;
typedef unordered_map<unsigned,StudentsData> students_type;

void add_students (const table_type&, students_type&);
void add_exams (const table_type&, students_type&, unsigned int x);
void print_map(std::unordered_map<unsigned, StudentsData> const &m);

int main () {

    string filename_students = "/home/bonni/Documents/APC/lab_3/Lab3-initial/initial_code/students.txt";
    string filename_exams = "/home/bonni/Documents/APC/lab_3/Lab3-initial/initial_code/exams.txt";

    students_type students;

    FileManager FM;

    // parse students file
    table_type fields = FM.parse_file(filename_students);
    for (size_t i = 0; i < fields.size(); i++)
    {
        for (size_t j = 0; j < fields[i].size(); j++)
        {
            std::cout << fields[i][j] << ", ";
        }
        std::cout << std::endl;
    }
    std::cout << "Puffo " << fields.size()<< " fields[1] :" << fields[1].size() << std::endl;
    unsigned int stud = fields.size();
    // add students to the map
    add_students(fields, students);
    print_map(students);
    // parse exams file
    fields = FM.parse_file(filename_exams);
    for (size_t i = 0; i < fields.size(); i++)
    {
        for (size_t j = 0; j < fields[i].size(); j++)
        {
            std::cout << fields[i][j] << ", ";
        }
        std::cout << std::endl;
    }
    
    std::cout << "Puffo " << fields.size()<< " fields[1] :" << fields[7].size() << std::endl;
    // add exams to the corresponding students, if they exist in the map
    add_exams(fields, students, stud);
    print_map(students);
    // compute and print average of students' grades
    
    for(auto const &pair: students){
        std::cout << pair.first << ": " << pair.second.average_grade() << std::endl;
    }
}

void add_students (const table_type& fields, students_type& students) {
    unsigned int j = 1;
    for (size_t i = 0; i < fields.size(); i++)
    {   
        unsigned long matricola = std::stoul(fields[i][0]);
        std::string n = fields[i][j];
        std::string s = fields[i][j+1];
        std::string birthdate = fields[i][j+2];
        StudentsData sd(n, s, birthdate);
        j=1;
        students.insert(std::make_pair(matricola, sd));
    }
}

void add_exams (const table_type& fields, students_type& students, unsigned int x){
    for (size_t i = x; i < fields.size(); i++)
    {unsigned long matricola = std::stoul(fields[i][0]);
        if (students.find(matricola) == students.end())
        {
            std::cerr << "Student not found" << std::endl;
        }
        else
        {
            unsigned long course_id = std::stoul(fields[i][1]);
            std::string date = (fields[i][2]);
            unsigned long grade = std::stoul(fields[i][3]);
            Exam e(course_id, date, grade);
            students.at(matricola).add_exam(e);
        }
    
    }
}
void print_map(std::unordered_map<unsigned, StudentsData> const &m){
    for (auto const &pair: m) {
        std::cout << "===================" << std::endl; 
        std::cout << pair.first << ": " << pair.second.get_name() << " " << pair.second.get_surname() << " " << pair.second.get_birthdate() << std::endl;
        pair.second.print_exams();
        std::cout << "===================" << std::endl;
    }
}