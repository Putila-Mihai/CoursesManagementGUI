//
// Created by ultra on 06.06.2023.
//

#ifndef QTLAB_SERVICE_H
#define QTLAB_SERVICE_H

#include "Contract.h"
#include "Repo.h"
#include <string>
#include <vector>
#include <functional>
#include "validator.h"
#include "Studii.h"
#include "export.h"
#include<memory>
#include "undo.h"
#include <map>

using std::unique_ptr;
using std::vector;
using std::function;
using std::map;

class service {
    repo &rep;
    //RepoLab lab;
    Validator &val;
    std::vector<unique_ptr<ActiuneUndo>> undoActions;
    contract_studii current_contract;

    /*
     * General funtion to filter the list
     * fct it's the funtion used to filter
     * return a list of contracts
     */
    vector<contract> filter(function<bool(const contract &)> fct);

    /*
     * General funtion to sort the list of contracts
     * lesser funtion that compare  2 contracts ,verify the relation between them
     * it can be any funtion that respect the structure (return bool and have 2 contract parameters
     * retunr a list of contracts by the given criteria
     */
    vector<contract> generalSort(bool (*lesser)(const contract &, const contract &));

public:
    service(repo &rep, Validator &val) : rep{rep}, val{val}{}

    service(const service &ot) = delete;
    contract_studii& get_contract(){
        return current_contract;
    }
    /*
     * return all contracts
     */
    const vector<contract> &getall() noexcept {
        return rep.getall();
    }

    /*
     * return all contracts that have more hours that a given number
     */
    vector<contract> filter_greater(int min_ore);

    /*
     * return all contracts that have save teacher as the given one
     */
    vector<contract> filter_teacher(string teacher);

    /*
     * sort the list by "denumire"
     */
    vector<contract> sort_denumire();

    /*
     * sort the list by "ore"
     */
    vector<contract> sort_tip_prof();

    /*
     * sort the list by "tip" and "profesor"
     */
    vector<contract> sort_ore();

    /*
     * add new contract
     * throw exception if arleady exist
     */
    void addcontract(const string &denumire, int ore, const string &tip, const string &profesor);

    /*
     * delete a contract from the list
     * throw exception if doesn't exist
     */
    void delete_s(const string &denumire);

    /*
     * modify a contract from  the list
     * throw exception if doesn't exist
     */
    void modify_s(const string &denumire, int ore, const string &tip, const string &profesor);

    /*
     * search an contract by it's disciplina
     * throw exception if the contract doesn't exist
     */
    const contract &search_s(const string &denumire);

    /*
    * add a couse to the contract by denumire
    *
    * @param dehnumire: name of the course  (string)
    *
    *
    * post: the course it's added to the contract
    * @throws: RepoException if the course doesn't exist
    */
    void addToContract(string denumire);

    /*
    * add a number of random courses to the contract
    *
    * @param number : number of courses
    *
    * @return: number of courses added
    * post: add a NUMBER of courses to the contract
    */
    int addRandomToContract(int number);

    /*
    * delete all courses from contract
    * post: the contract it's empty
    */
    void emptycontract();

    /*
    * return all courses in the contract
    */
    const vector<contract> &getAllCourses();

    void exportaCVS(std::string fName) const;

    void exportaHTML(std::string fName) const;

    void undo();

    map<string, int> service_raport();

    void repolab();

};

void test_service();
#endif //QTLAB_SERVICE_H
