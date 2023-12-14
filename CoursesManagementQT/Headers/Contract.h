//
// Created by ultra on 06.06.2023.
//

#ifndef QTLAB_CONTRACT_H
#define QTLAB_CONTRACT_H

#include <iostream>
#include <string>
#include <utility>

using std::string;
using std::cout;

class contract {
private:
    string denumire;
    int ore;
    string tip;
    string profesor;
public:
    [[nodiscard]] int get_ore() const;

    [[nodiscard]] string get_denumire() const;

    [[nodiscard]] string get_tip() const;

    [[nodiscard]] string get_profesor() const;

    void set_ore(const int ore);

    void set_denumire(const string denumire);

    void set_tip(const string tip);

    void set_profesor(const string profesor);

    contract(string denumire, int ore, string tip, string profesor) : denumire{std::move(denumire)}, ore{ore},
                                                                      tip{std::move(tip)},
                                                                      profesor{std::move(profesor)} {}

    /*contract(const contract &ot) : denumire{ot.denumire}, ore{ot.ore}, tip{ot.tip}, profesor{ot.profesor} {
        cout << "Copy Called\n";
    }*/

};

/*
compares 2 contracts by their denumire
return true if p1 denumire it's bigger
*/
bool cmpDenumire(const contract& p1, const contract& p2);

/*
compares 2 contracts by their ore
return true if p1 ore it's bigger
*/
bool cmpore(const contract& p1, const contract& p2);

void test_contract();
#endif //QTLAB_CONTRACT_H
