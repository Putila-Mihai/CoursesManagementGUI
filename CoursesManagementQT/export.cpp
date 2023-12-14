#include "Headers/export.h"
#include "Headers/Contract.h"
#include <fstream>
#include <string>
#include <vector>
void exportToCVS(const std::string& fName,const std::vector<contract>& c) {
    std::ofstream out(fName, std::ios::trunc);
    if (!out.is_open()) {
        throw ("Unable to open file:" + fName);
    }
    for (const auto& r : c) {
        out << r.get_denumire()<<",";
        out << r.get_tip() << ",";
        out << r.get_profesor() << ",";
        out << r.get_ore() << std::endl;
    }
    out.close();
}
/*
Scrie in fisierul fName lista de animale
in format HTML
arunca PetException daca nu poate crea fisierul
*/
void exportToHTML(const std::string& fName, const std::vector<contract>& c) {
    std::ofstream out(fName, std::ios::trunc);
    if (!out.is_open()) {
        throw ("Unable to open file:" + fName);
    }
    out << "<html><body>" << std::endl;
    out << "<table border=\"1\" style=\"width:100 % \">" << std::endl;
    for (const auto& r : c) {
        out << "<tr>" << std::endl;
        out << "<td>" << r.get_denumire() << "</td>"<<std::endl;
        out << "<td>" << r.get_ore() << "</td>" << std::endl;
        out << "<td>" << r.get_profesor() << "</td>" << std::endl;
        out << "<td>" << r.get_tip() << "</td>" << std::endl;
        out << "</tr>" << std::endl;
    }
    out << "</table>" << std::endl;
    out << "</body></html>" << std::endl;
    out.close();
}