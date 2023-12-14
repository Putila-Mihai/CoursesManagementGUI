//
// Created by ultra on 06.06.2023.
//

#ifndef QTLAB_STUDII_H
#define QTLAB_STUDII_H

#include "Contract.h"
#include <vector>
#include <algorithm>
#include <random>    // std::default_random_engine
#include <chrono>

using std::vector;

class contract_studii {
private:
    vector<contract> courses;
public:
    /*
     * default constructor
     */
    contract_studii()=default;
    /*
     * add a course to  contract
     * @param c: the course that will be added
     *
     * post the course will be added to the list
     */
    void add_contract(const contract& c);
    /*
     * delete all couses from the contract
     * post: the list will be empty
     */
    void empty_contract();
    /*
     * add random number of courses to the list
     * @ param originalcourses: the list of courses from where they are selected
     * @param number : number of courses that will be added
     * post: the courses will  be added to the list
     */
    void addRandom(vector<contract>originalcourses,int number);
    /*
     * return a vector that cointain all courses in the contract
     */
    const vector<contract> & getallcourses() const;
};

#endif //QTLAB_STUDII_H
