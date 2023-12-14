#include "Headers/validator.h"
#include <assert.h>
#include <sstream>

void Validator::validate(const contract &c) {
    vector<string> msgs;
    if (c.get_ore() < 0) msgs.emplace_back("numarul de ore trebuie sa fie un numar pozitiv");
    if (c.get_tip() == "") msgs.emplace_back("tip vid!");
    if (c.get_profesor() =="")msgs.emplace_back("profesor vid");
    if (c.get_denumire() == "") msgs.emplace_back("denumire vida!");
    if (!msgs.empty()) {
        throw ValidateException(msgs);
    }
}