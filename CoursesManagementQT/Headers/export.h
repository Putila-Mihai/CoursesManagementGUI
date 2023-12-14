//
// Created by ultra on 06.06.2023.
//

#ifndef QTLAB_EXPORT_H
#define QTLAB_EXPORT_H
#include <string>
#include <vector>
#include "Contract.h"
/*
Scrie in fisierul fName lista de cursuri
in format CSV
arunca Exception daca nu poate crea fisierul
*/
void exportToCVS(const std::string& fName,const std::vector<contract>& c);
/*
Scrie in fisierul fName lista de animale
in format HTML
arunca Exception daca nu poate crea fisierul
*/
void exportToHTML(const std::string& fName, const std::vector<contract>& c);
#endif //QTLAB_EXPORT_H
