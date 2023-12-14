#include "Headers/Service.h"
#include <assert.h>
#include <fstream>
void service::addcontract(const std::string &denumire, int ore, const std::string &tip, const std::string &profesor) {
    contract c{denumire, ore, tip, profesor};
    val.validate(c);
    rep.store(c);
    undoActions.push_back(std::make_unique<UndoAdauga>(rep, c));
}

void service::delete_s(const string &denumire) {

    contract c = this->search_s(denumire);
    rep.delete_contract(denumire);
    undoActions.push_back(std::make_unique<UndoSterge>(rep, c));
}

void service::modify_s(const std::string &denumire, int ore, const std::string &tip, const std::string &profesor) {
    contract c = this->search_s(denumire);
    undoActions.push_back(std::make_unique<UndoModifica>(rep, c));
    rep.modify_contract(denumire, ore, tip, profesor);
}

const contract &service::search_s(const string &denumire) {
    return rep.find_by_d(denumire);
}

vector<contract> service::filter(function<bool(const contract &)> fct) {
    vector<contract> rez;
    /*for (const auto &c: rep.getall()) {
        if (fct(c)) {
            rez.push_back(c);
        }
    }*/
    std::copy_if(rep.getall().begin(), rep.getall().end(), back_inserter(rez),
                 [=](const contract &c) { return fct(c); });
    return rez;
}

vector<contract> service::filter_greater(int min_ore) {
    return filter([min_ore](const contract &c) {
        return c.get_ore() > min_ore;
    });
}

vector<contract> service::filter_teacher(string teacher) {
    return filter([teacher](const contract &c) {
        return c.get_profesor() == teacher;
    });
}

vector<contract> service::generalSort(bool (*lesser)(const contract &, const contract &)) {
    vector<contract> rez{rep.getall()};
    /*for (size_t i = 0; i < rez.size(); i++) {
        for (size_t j = i + 1; j < rez.size(); j++) {
            if (!lesser(rez[i], rez[j])) {
                contract aux = rez[i];
                rez[i] = rez[j];
                rez[j] = aux;
            }
        }
    }*/
    std::sort(rez.begin(), rez.end(), [lesser](const contract &c1, const contract &c2) { return lesser(c1, c2); });
    return rez;
}

vector<contract> service::sort_denumire() {
    return generalSort(cmpDenumire);
}

vector<contract> service::sort_ore() {
    return generalSort(cmpore);
}

vector<contract> service::sort_tip_prof() {
    return generalSort([](const contract &c1, const contract &c2) {
        if (c1.get_tip() == c2.get_tip()) {
            return c1.get_profesor() < c2.get_profesor();
        }
        return c1.get_tip() < c2.get_tip();
    });
}
/////////////////////////////////////////Lab 89////////////////////////////////////

void service::addToContract(std::string denumire) {
    const contract& c = rep.find_by_d(denumire);
    current_contract.add_contract(c);
}

int service::addRandomToContract(int number) {
    current_contract.addRandom(this->getall(), number);
    return current_contract.getallcourses().size();
}

void service::emptycontract() {
    current_contract.empty_contract();
}

const vector<contract> &service::getAllCourses() {
    return current_contract.getallcourses();
}
void service::exportaCVS(std::string fName) const {
    exportToCVS(fName,current_contract.getallcourses());
}

void service::exportaHTML(std::string fName) const {
    exportToHTML(fName, current_contract.getallcourses());
}
void service::undo(){
    if (undoActions.empty()) {
        throw std::exception();
    }

    undoActions.back()->doUndo();
    undoActions.pop_back();

}
//void service::repolab() {
//    try {
//        lab.verify();
//    }
//    catch(string s){
//        return;
//    }
//}
/////////////////////////////////////////TEST////////////////////////////////////
void testUndo() {
    repo rep;
    Validator val;
    RepoLab lab(0);
    service ctr{rep, val};
    ctr.addcontract("aaa",2 ,"bbb", "a");
    ctr.addcontract("ccc",3 ,"bb", "b");
    ctr.addcontract("bbb",4 ,"b", "c");
    ctr.undo();
    assert(ctr.getall().size() == 2);
    ctr.undo();
    ctr.undo();
    assert(ctr.getall().size() == 0);
}
void test_add_service() {
    repo rep;
    Validator val;
    RepoLab lab(0);
    service ctr{rep, val};
    ctr.addcontract("a", 2, "a", "c");
    assert(ctr.getall().size() == 1);
    try {
        ctr.addcontract("", 4, "a", "a");
        assert(false);
    }
    catch (ValidateException & ve) {
        assert(ve.getErrorMessages()=="denumire vida!\n");
    }
    assert(ctr.search_s("a").get_ore() == 2);
    //incerc sa adaug ceva ce existadeja
}

void test_deletes() {
    repo rep;
    Validator val;
    RepoLab lab(0);
    service ctr{rep, val};
    ctr.addcontract("a", 2, "a", "c");
    ctr.addcontract("b", 2, "5", "c");
    ctr.delete_s("a");
    assert(ctr.getall().size() == 1);

}

void test_modifys() {
    repo rep;
    Validator val;
    RepoLab lab(0);
    service ctr{rep, val};
    ctr.addcontract("a", 2, "a", "c");
    ctr.modify_s("a", 23, "sd", "asdfa");
    assert(ctr.getall().front().get_ore() == 23);

}

void test_filter() {
    repo rep;
    Validator val;
    RepoLab lab(0);
    service ctr{rep, val};
    ctr.addcontract("a", 2, "a", "c");
    ctr.addcontract("b", 26, "sd", "d");
    ctr.addcontract("c", 222, "a", "c");
    assert(ctr.filter_greater(25).size() == 2);
    assert(ctr.filter_teacher("d").size() == 1);
}

void testSort() {
    repo rep;
    Validator val;
    RepoLab lab(0);
    service ctr{rep, val};
    ctr.addcontract("asdasd", 323, "a", "d");
    ctr.addcontract("b", 22, "sd", "d");
    ctr.addcontract("c", 222, "a", "c");

    auto firstC = ctr.sort_denumire().front();
    assert(firstC.get_denumire() == "asdasd");

    firstC = ctr.sort_ore()[0];
    assert(firstC.get_tip() == "sd");

    firstC = ctr.sort_tip_prof()[0];
    assert(firstC.get_ore() == 222);
}

/////////////////////////////////////////////////////////////////////////

void testCoursesContract() {
    repo testRepo;
    Validator testVal;
    RepoLab lab(0);
    service ctr{testRepo, testVal};

    ctr.addcontract("a", 1, "aa", "ion");
    ctr.addcontract("b", 22, "bb", "ionel");
    ctr.addcontract("c", 222, "cc", "ionut");
    ctr.addcontract("asdasd", 3333, "dd", "ioan");
    ctr.addcontract("d", 44, "ee", "iustin");
    ctr.addcontract("e", 6, "ff", "iacob");

    ctr.addRandomToContract(4);
    assert(ctr.getAllCourses().size() == 4);
    ctr.emptycontract();
    assert(ctr.getAllCourses().size() == 0);

    ctr.addRandomToContract(20);
    //putem adauga doar 6 melodii (fara sa se repete)
    assert(ctr.getAllCourses().size() == 6);

    ctr.emptycontract();
    ctr.addToContract("a");
    assert(ctr.getAllCourses().size() == 1);

    try {
        ctr.addToContract("sirop");
        assert(false);
    }
    catch (RepoException &) {
        assert(true);
    }

    map<string,int>m =ctr.service_raport();


}
void testExporta() {
    repo rep;
    Validator testVal;
    RepoLab lab(0);
    service ctr{rep, testVal};
    ctr.addcontract("aaa",2,"bbb","cscc");
    ctr.addcontract("bbb",2,"ddd","cccsd");
    ctr.addcontract("ccc",2,"bbbasd","casdcc");
    ctr.addRandomToContract(3);
    ctr.exportaCVS("testExport.cvs");
    std::ifstream in("testExport.cvs");
    assert(in.is_open());
    int countLines = 0;
    while (!in.eof()) {
        string line;
        in >> line;
        countLines++;
    }
    in.close();
    assert(countLines == 4);//avem o linie pentru fiecare pet + o linie goala
    ctr.exportaHTML("testExport.html");
    in.open("testExport.html");
    assert(in.is_open());
}

void test_service() {
    test_add_service();
    test_deletes();
    test_modifys();
    test_filter();
    testSort();
    testCoursesContract();
    testExporta();
    testUndo();
}

map<string,int> service::service_raport() {
    map<string ,int> rez;
    //for (int i = 0; i < current_contract.getallcourses().size(); i++)
    for (const auto e:current_contract.getallcourses()){
        if(rez.empty())
        {
            rez.insert({e.get_tip(), 1});
        }
        for (auto itr = rez.begin(); itr != rez.end(); ++itr){
            if(itr->first==e.get_tip())
            {
                itr->second++;
            }
            else {
                rez.insert({e.get_tip(), 1});
            }
        }
    }
    return rez;

}