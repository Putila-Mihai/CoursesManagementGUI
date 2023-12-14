#include "Headers/Repo.h"
#include <assert.h>
#include <iostream>
#include <sstream>
#include <algorithm>
#include "Headers/validator.h"
#include <fstream>
#include<exception>
using std::ostream;
using std::stringstream;
void RepoLab::store(const contract &c) {
    all.push_back(c);
}
void RepoLab::verify(){
    float random =(float) rand() / (float)RAND_MAX;
    if(this->probabilitate>random)
        throw std::exception();
    else {
        store(contract("a", 2, "b", "c"));
        cout << "adaugat";
    }
}
void RepoLab::delete_contract(const std::string &denumire) {
    int ok = 0;
    for (int i = 0; i < all.size(); i++) {
        if (all[i].get_denumire() == denumire) {
            ok = 1;
            all.erase(all.begin() + i);
            break;
        }
    }
    if (ok == 0) {
        throw RepoException("Acest contract nu exista");
    }
}
void repo::store(const contract &c) {
    if (exist(c)) {
        throw RepoException("Exista deja acest contract:" + c.get_denumire());
    }
    all.push_back(c);
}

void repo::delete_contract(const std::string &denumire) {
    int ok = 0;
    for (int i = 0; i < all.size(); i++) {
        if (all[i].get_denumire() == denumire) {
            ok = 1;
            all.erase(all.begin() + i);
            break;
        }
    }
    if (ok == 0) {
        throw RepoException("Acest contract nu exista");
    }
}

void repo::modify_contract(const string &denumire, const int &ore, const string &tip, const string &profesor) {
    int ok = 0;
    for (int i = 0; i < all.size(); i++) {
        if (all[i].get_denumire() == denumire) {
            ok = 1;
            all[i].set_profesor(profesor);
            all[i].set_ore(ore);
            all[i].set_tip(tip);
            break;
        }
    }
    if (ok == 0) {
        throw RepoException("Acest contract nu exista");
    }

}

bool repo::exist(const contract &c) {
    try {
        find(c.get_denumire(), c.get_tip(), c.get_profesor());
        return true;
    }
    catch (RepoException) {
        return false;
    }
}

const contract & repo::find(string denumire, string tip, string profesor){
    /*for (const auto &c: all) {
        if (c.get_denumire() == denumire && c.get_profesor() == profesor && c.get_tip() == tip) {
            return c;
        }
    }
    throw RepoException("Nu exista acest contract");*/
    /*const auto found = std::find_if(all.begin(), all.end(), [=](const contract &pp) {
        return pp.get_denumire() == denumire && pp.get_tip() == tip && pp.get_profesor() == profesor;
    });
    if (found == all.end()) {
        throw RepoException("Nu exista acest contract");
    }
    return *found;*/
    vector<contract>::iterator f = std::find_if(this->all.begin(), this->all.end(),
                                                [=](const contract& s) {
                                                    return s.get_denumire() == denumire && s.get_tip() == tip && s.get_profesor() == profesor;
                                                });

    if (f != this->all.end())
        return (*f);
    else
        throw RepoException("Melodia cu titlul "+denumire+" si artistul "+profesor +" nu exista in lista.\n");
}

const vector<contract> &repo::getall() const noexcept {
    return all;
}

ostream &operator<<(ostream &out, const RepoException &ex) {
    out << ex.msg;
    return out;
}

const contract &repo::find_by_d(const string &denumire) const {
    /*for (const auto &c: all) {
        if (c.get_denumire() == denumire) {
            return c;
        }*/
    const auto found = std::find_if(all.begin(), all.end(), [=](const contract &pp) {
        return pp.get_denumire() == denumire;
    });
    if (found == all.end()) {
        throw RepoException("Nu exista acest curs");
    }
    return *found;

}

///////////////////////////////////////////////////





//!!!!!!!!!!!!!!!!!!!!!!TEST!!!!!!!!!!!!!!!!!!!!!!!!



void test_adauga() {
    repo rep;
    rep.store(contract{"OOP", 20, "Info", "mihai"});
    assert(rep.getall().size() == 1);
    assert(rep.find("OOP", "Info", "mihai").get_denumire() == "OOP");
    assert(rep.find_by_d("OOP").get_tip() == "Info");
    try {
        rep.store(contract{"OOP", 20, "Info", "mihai"});
        assert(false);
    }
    catch (const RepoException &) {
        assert(true);
    }
    try {
        rep.find("c", "c", "c");
        assert(false);
    }
    catch (const RepoException &e) {
        stringstream os;
        os << e;
        assert(os.str().find("exista") >= 0);
    }
    try {
        rep.find_by_d("c");
        assert(false);
    }
    catch (const RepoException &e) {
        stringstream os;
        os << e;
        assert(os.str().find("exista") >= 0);
    }
}

void test_cauta() {
    repo rep;
    rep.store(contract{"a", 20, "a", "a"});
    rep.store(contract{"b", 20, "b", "b"});

    auto c = rep.find("a", "a", "a");
    assert(c.get_denumire() == "a");
    assert(c.get_profesor() == "a");
    assert(c.get_tip() == "a");
    assert(c.get_ore() == 20);

    //throw exception
    try {
        rep.find("a", "b", "c");
        assert(false);
    }
    catch (RepoException &) {
        assert(true);
    }
}

void test_delete() {
    repo rep;
    rep.store(contract{"a", 20, "a", "a"});
    rep.store(contract{"b", 20, "b", "b"});
    rep.delete_contract("a");
    assert(rep.getall().size() == 1);
    try {
        rep.delete_contract("sad");
        assert(false);
    }
    catch (const RepoException &) {
        assert(true);
    }
}

void test_modify() {
    repo rep;
    rep.store(contract{"a", 20, "a", "a"});
    rep.modify_contract("a", 40, "b", "s");
    try {
        rep.modify_contract("assag", 40, "b", "s");
        assert(false);
    }
    catch (const RepoException &) {
        assert(true);
    }
}
//////////////////////////////////////////////////////



void RepoFile::loadFromFile(){
    std::ifstream in(fName);
    if (!in.is_open()) { //verify if the stream is opened
        throw ("Unable to open file:"+fName);
    }
    while (!in.eof()) {
        std::string denumire;
        in >> denumire;
        int ore;
        in>>ore;
        std::string tip;
        in >> tip;
        std::string profesor;
        in >> profesor;
        if (in.eof()) {	//nu am reusit sa citesc numarul
            break;
        }
        contract c{denumire,ore,tip,profesor};
        repo::store(c);
    }
    in.close();
}

void RepoFile::writeToFile() {
    std::ofstream out(fName);
    if (!out.is_open()) { //verify if the stream is opened
        std::string msg("Unable to open file:");
        throw (msg);
    }
    for (auto& p:getall()) {
        out << p.get_denumire();
        out << std::endl;
        out << p.get_ore();
        out << std::endl;
        out << p.get_tip();
        out << std::endl;
        out << p.get_profesor();
        out << std::endl;
    }
    out.close();
}

void testFileRepo() {
    std::ofstream out("test.txt", std::ios::trunc);
    out.close();//creez un fisier gol
    RepoFile repF{"test.txt"};
    repF.store(contract{"aaa", 12, "bbb", "asd"});
    RepoFile repF2{"test.txt"};
    auto p = repF2.find_by_d("aaa");
    assert(p.get_ore() == 12);
    try {
        repF2.find_by_d("aaa2");
        assert(false);
    }
    catch (RepoException &) {
        assert(true);
    }
    repF2.delete_contract("aaa");
    assert(repF2.getall().size()==0);
    try {
        repF2.delete_contract("aaa2");
        assert(false);
    }
    catch (RepoException & e) {
        assert(!e.getErrorMessage().empty());
    }

    RepoFile repF3{ "test.txt" };
    assert(repF3.getall().size() == 0);



}
void testeRepo() {
    test_adauga();
    test_cauta();
    test_delete();
    test_modify();
    testFileRepo();
}