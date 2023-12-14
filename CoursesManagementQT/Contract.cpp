#include "Headers/Contract.h"
#include <assert.h>

int contract::get_ore() const {
    return ore;
}

string contract::get_denumire() const {
    return denumire;
}

string contract::get_tip() const {
    return tip;
}

string contract::get_profesor() const {
    return profesor;
}

void contract::set_ore(const int new_ore) {
    ore = new_ore;
}

void contract::set_denumire(const string new_denumire) {
    denumire = new_denumire;
}

void contract::set_tip(const string new_tip) {
    tip = new_tip;
}

void contract::set_profesor(const string new_profesor) {
    profesor = new_profesor;
}

bool cmpDenumire(const contract& p1, const contract& p2){
    return p1.get_denumire() < p2.get_denumire();
}


bool cmpore(const contract& p1, const contract& p2){
    return p1.get_ore() < p2.get_ore();
}

void test_contract() {
    contract c{"j", 20, "b", "c"};
    contract c2{"nfg",23,"sadasd","asd"};
    c.set_denumire("b");
    assert(c.get_denumire() == "b");
    c.set_ore(10);
    assert(c.get_ore() == 10);
    c.set_tip("y");
    assert(c.get_tip() == "y");
    c.set_profesor("z");
    assert(c.get_profesor() == "z");
    assert(cmpore(c,c2) == 1);
    assert(cmpDenumire(c,c2) == true);

}