#include "Headers/validator.h"
#include "Headers/Repo.h"
#include "Headers/Service.h"
#include "Headers/console.h"
#include "Headers/Contract.h"
#include <iostream>
#include <QApplication>
#include <QPushButton>
#include "GUI.h"
#include "StudiiGUI.h"
void test_all() {
    testeRepo();
    test_service();
    test_contract();
}

void add5(service &ctr) {
    ctr.addcontract("OOP", 25, "Info", "Mihai");
    ctr.addcontract("SD", 15, "Math", "Ion");
    ctr.addcontract("SDA", 19, "Info", "Ionel");
    ctr.addcontract("OS", 25, "Info", "Ionut");
    ctr.addcontract("Geo", 19, "Math", "Ion");
    ctr.addcontract("AI", 30, "Info", "Mihai");
    ctr.addcontract("Algebra", 16, "Math", "Ramirez");
    ctr.addcontract("Analiza", 20, "Math", "Alexandra");
    ctr.addcontract("Retele", 25, "Info", "Justin Time");
    ctr.addcontract("Securitate Cybernetica", 30, "Info", "Ioan");
}
int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    test_all();
    repo rep;
    Validator val;
    service ctr{rep, val};
    add5(ctr);
    contractGUI g{ctr};
    g.resize(800,500);

    g.show();
    CosGUI* cosGUI = new CosGUI{ctr.get_contract()};
    cosGUI->resize(800,500);
    cosGUI->show();
    return QApplication::exec();
}