//
// Created by Danilo Ardagna on 18/11/2019.
//

#include "StudentsData.h"

using std::string;

StudentsData::StudentsData(const string& name, const string& lastName, const string& birthDate):
    name(name), last_name(lastName), birth_date(birthDate) {}

void StudentsData::add_exam(const Exam& e) {
    exams.push_back(e);
}

std::string StudentsData::get_name() const {
        return name;
    }
std::string StudentsData::get_surname() const {
        return last_name;
    }
std::string StudentsData::get_birthdate() const {
        return birth_date;
    }
void StudentsData::print_exams() const {
    for (size_t i = 0; i < exams.size(); i++)
    {
        std::cout << exams[i].getCourseId() << " " << exams[i].getDate() << " " << exams[i].getGrade() << std::endl;
    }
    
}
float StudentsData::average_grade() const {
    float sum = 0.;

    for (const Exam& e : exams)
        sum += e.getGrade();

    return sum/exams.size();
}
