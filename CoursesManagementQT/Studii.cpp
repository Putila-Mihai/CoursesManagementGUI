//
// Created by ultra on 18.05.2023.
//
#include "Headers/Studii.h"
using std::shuffle;

void contract_studii::add_contract(const contract &c) {
    this->courses.push_back(c);
}
void contract_studii::empty_contract() {
    this->courses.clear();
}

void contract_studii::addRandom(vector<contract> originalcourses, int number) {
    shuffle(originalcourses.begin(), originalcourses.end(),std::default_random_engine(std::random_device{}()));
    while(courses.size() < number && originalcourses.size() > 0) {
        courses.push_back(originalcourses.back());
        originalcourses.pop_back();
    }
}
const vector<contract> & contract_studii::getallcourses() const {
    return this->courses;
}