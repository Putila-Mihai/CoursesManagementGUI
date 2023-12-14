//
// Created by ultra on 06.06.2023.
//
#ifndef QTLAB_CONSOLE_H
#define QTLAB_CONSOLE_H
#include "Service.h"
#include "Contract.h"

class ConsoleUI {
    service &ctr;

    /*
    Read a contract from input and addd it to the list
    */
    void addUI();

    /*
    Print the list of contracts
    */
    static void print(const vector<contract> &contracts);

    /*
     * delete a contract
     * throw exception if the contract doesn't exist
     */
    void delete_UI();

    /*
     * modify a contract
     * throw exception if the contract doesn't exist
     */
    void modify_UI();

    /*
     * search an contract by it's disciplina
     * throw exception if the contract doesn't exist
     */
    void search_UI();

    /*
     * filter all contract by their number of hours
     */
    void filter_h_UI();

    /*
     * filter all contract by their teacher
     */
    void filter_t_UI();

    /*
     * sort the list of contract by "denumire"
     */
    void sort_d_UI();

    /*
     * sort the list of contracts by "ore"
     */
    void sort_o_UI();

    /*
     * sort the list of contracts by "tip" and "profesor"
     */
    void sort_tp_UI();

    ////////////////////////////////
    void contract_UI();

    void AddToContract_UI();

    void AddRandom_UI();

    void EmptyContract_UI();

    void printContractMenu();

    void exportCVS();

    void exportHTML();

    void replab();



public:
    ConsoleUI(service &ctr) : ctr{ctr} {
    }

    ConsoleUI(const ConsoleUI &ot) = delete;

    /*
     * start the app
     */
    void start();
    void raport();
};

#endif //QTLAB_CONSOLE_H
