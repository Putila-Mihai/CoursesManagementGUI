//
// Created by ultra on 06.06.2023.
//

#ifndef QTLAB_VALIDATOR_H
#define QTLAB_VALIDATOR_H

#include "Contract.h"
#include <string>
#include <vector>

using std::string;
using std::vector;
using std::ostream;

class ValidateException {
    vector<string> msgs;
public:
    ValidateException(const vector<string> &errors) : msgs{std::move(errors)} {}
    string getErrorMessages(){
        string fullMsg = "";
        for (const string e : msgs) {
            fullMsg += e + "\n";
        }
        return fullMsg;
    }

};


class Validator {
public:
    void validate(const contract &c);

};


#endif //QTLAB_VALIDATOR_H
