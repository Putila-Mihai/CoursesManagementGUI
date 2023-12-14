//
// Created by ultra on 06.06.2023.
//

#ifndef QTLAB_REPO_H
#define QTLAB_REPO_H

#include "Contract.h"
#include <utility>
#include <vector>
#include <string>
#include <ostream>
#include <map>
using std::map;
using std::vector;
using std::string;
using std::ostream;
class AbstractRepo{
protected:
    vector<contract> all;
public:
    AbstractRepo()=default;
    virtual void store(const contract &c) = 0;
    virtual void delete_contract(const string &denumire) = 0;

};

class RepoLab:public AbstractRepo{
private:
    double probabilitate;
public:
    RepoLab(double p):AbstractRepo(){
        probabilitate=p;
    };
    ~RepoLab()=default;
    void store(const contract& c)override;
    void delete_contract(const string &denumire) override;
    void verify();
};
class repo :public AbstractRepo {
    //vector<contract> all;

    /*
     * Funtion verify if the contract arleady exist in the list
     * return ture if exist and false either
     */
    [[nodiscard]] bool exist(const contract &c);

public:
    repo():AbstractRepo(){};
    virtual ~repo()=default;

    /*
     * save contract to list
     * throw exception if arleady exist
     */
    void store(const contract &c) override;

    /*
     * search for a contract in list
     * throw expection if doesn't exist
     */
    const contract & find( string denumire,  string tip, string profesor);

    /*
     * search for a contract in list
     * throw expection if doesn't exist
     */
    [[nodiscard]] const contract &find_by_d(const string &denumire) const;

    /*
     * return all contracts from the list
     */
    [[nodiscard]] const vector<contract> &getall() const noexcept;

    /*
     * delete a contract from the list
     * throw exception if the contract doesn't exist
     */
    void delete_contract(const string &denumire)override;

    /*
     * modify the contract from the list
     * throw exception if the contract doesn't exist
     */
    void modify_contract(const string &denumire, const int &ore, const string &tip, const string &profesor);

};

class RepoException {
    string msg;
public:
    explicit RepoException(string exc) : msg{std::move(exc)} {}
    string getErrorMessage()  {
        return this->msg;
    }
    friend ostream &operator<<(ostream &out, const RepoException &ex);
};

ostream &operator<<(ostream &out, const RepoException &ex);


class RepoFile :public repo {
private:
    std::string fName;
    void loadFromFile();
    void writeToFile();
public:
    explicit RepoFile(std::string fName) :repo(), fName{std::move( fName )} {
        loadFromFile();//incarcam datele din fisier
    }
    void store(const contract& p) override {
        repo::store(p);
        writeToFile();
    }
    void delete_contract(const string &denumire) override {
        repo::delete_contract(denumire);
        writeToFile();
    }
};



void testrepos();
void testeRepo();
#endif //QTLAB_REPO_H
