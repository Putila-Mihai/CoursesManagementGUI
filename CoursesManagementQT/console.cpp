#include "Headers/console.h"
#include "Headers/Contract.h"
#include<iostream>
#include <string>

using std::cout;
using std::cin;


void ConsoleUI::print(const vector<contract> &contracts) {
    cout << "Contracte:Denumire || Ore || Tip || Profesor";
    for (const auto &c: contracts) {
        cout << "\n                " << c.get_denumire() << " || " << c.get_ore() << " || " << c.get_tip() << " || "
             << c.get_profesor();
    }
}

void ConsoleUI::delete_UI() {
    string denumire;
    cout << '\n' << "Introduceti denumire: ";
    cin >> denumire;
    ctr.delete_s(denumire);
    cout << "sters cu succes\n";
}

void ConsoleUI::addUI() {
    string denumire, tip, profesor;
    int ore;
    cout << '\n' << "Introduceti denumire: ";
    cin >> denumire;
    cout << "Introduceti numar de ore";
    cin >> ore;
    cout << "Introduceti tipul: ";
    cin >> tip;
    cout << "Introduceti Profesor:  ";
    cin >> profesor;
    try {
        ctr.addcontract(denumire, ore, tip, profesor);
        cout << "Adaugat cu succes";
    }
    catch (RepoException& re) {
        cout << re.getErrorMessage();
    }
    catch (ValidateException& ve) {
        cout << "Melodia nu este valida!\n";
        cout << ve.getErrorMessages();
    }
}

void ConsoleUI::modify_UI() {
    string denumire, tip, profesor;
    int ore;
    cout << '\n' << "Introduceti denumire: ";
    cin >> denumire;
    cout << "Introduceti numar de ore";
    cin >> ore;
    cout << "Introduceti tipul: ";
    cin >> tip;
    cout << "Introduceti Profesor:  ";
    cin >> profesor;
    ctr.modify_s(denumire, ore, tip, profesor);
    cout << "Modificat cu  succes";
}

void ConsoleUI::search_UI() {
    string denumire;
    cout << '\n' << "Introduceti denumire: ";
    cin >> denumire;
    cout << "\n                " << ctr.search_s(denumire).get_denumire() << " || " << ctr.search_s(denumire).get_ore()
         << " || " << ctr.search_s(denumire).get_tip() << " || "
         << ctr.search_s(denumire).get_profesor();
}

void ConsoleUI::filter_h_UI() {
    int min_h;
    cout << "Introduceti numarul minim de ore: ";
    cin >> min_h;
    print(ctr.filter_greater(min_h));
}

void ConsoleUI::filter_t_UI() {
    string t;
    cout << "Introduceti Profesorul: ";
    cin >> t;
    print(ctr.filter_teacher(t));
}

void ConsoleUI::sort_d_UI(){
    print(ctr.sort_denumire());
}
void ConsoleUI::sort_o_UI(){
    print(ctr.sort_ore());
}
void ConsoleUI::sort_tp_UI(){
    print(ctr.sort_tip_prof());
}
void ConsoleUI::start() {
    while (true) {
        cout << "\nMeniu:\n";
        cout
                << "[0]Stop [1]Adauga [2]Tipareste [3]Sterge [4]Modificare [5]Cautare disciplina [6]Filtrare numar de ore\n[7]Filtrare dupa profesor: "
                   "[8]Sortare dupa denumire [9]Sortare dupa ora: [10]Sortare dupa tip si profesor"
                   "\n[11]Meniu Contract[11] [12]Undo ";
        int cmd;
        cin >> cmd;
        try {
            switch (cmd) {
                case 1:
                    addUI();
                    break;
                case 2:
                    print(ctr.getall());
                    break;
                case 3:
                    delete_UI();
                    break;
                case 4:
                    modify_UI();
                    break;
                case 5:
                    search_UI();
                    break;
                case 6:
                    filter_h_UI();
                    break;
                case 7:
                    filter_t_UI();
                    break;
                case 8:
                    sort_d_UI();
                    break;
                case 9:
                    sort_o_UI();
                    break;
                case 10:
                    sort_tp_UI();
                    break;
                case 11:
                    contract_UI();
                    break;
                case 12:
                    try {
                        ctr.undo();
                        print(ctr.getall());
                    }
                    catch (std::exception& ex)
                    {
                        std::cout<<"Nu mai exista operatii\n";
                    }
                    break;
//                case 13:
//                    replab();
//                    break;
                case 0:
                    return;
                default:
                    cout << "comanda invalida\n";
                    break;
            }
        }
        catch (RepoException &ex) {
            cout << ex.getErrorMessage() << '\n';
        }
        catch (ValidateException &ex) {
            cout << ex.getErrorMessages() << '\n';
        }
    }
}
void ConsoleUI::printContractMenu() {
    cout << "\nMENIU CONTRACT"<< '\n';
    cout << "1. Adauga curs in contract" << '\n';
    cout << "2. Adauga cursuri random in contract" << '\n';
    cout << "3. Goleste contract" << '\n';
    cout << "4. Afiseaza contract curent" << '\n';
    cout << "5. Inapoi la meniul principal" << '\n';
    cout << "6. exporta CVS" << '\n';
    cout << "7. export html" << '\n';
}

void ConsoleUI::AddToContract_UI() {
    string denumire;
    cout<<"denumirea cursului este:";
    cin>>denumire;
    try {
        ctr.addToContract(denumire);
        cout << "Adaugat cu succes\n";
    }
    catch (RepoException& re) {
        cout << re.getErrorMessage();
    }
    catch (ValidateException& ve) {
        cout << "Cursul nu este valid!\n";
        cout << ve.getErrorMessages();
    }


}
void ConsoleUI::AddRandom_UI(){
    int number;
    cout << "numarul de cursuri:";
    cin >> number;


    try {
        int howmany = ctr.addRandomToContract(number);
        cout << "S-au adaugat " << howmany << " cursuri in contract.\n";
    }
    catch (RepoException& re) {
        cout << re.getErrorMessage();
    }
}
void ConsoleUI::EmptyContract_UI(){
    ctr.emptycontract();
    cout << "S-au sters toate cursurile din contractul curent.\n";
}
void ConsoleUI::exportCVS() {
    cout<<"Numele fisierului de export:";
    string s;
    cin>>s;
    exportToCVS(s,ctr.getAllCourses());
}
void ConsoleUI::exportHTML() {
    cout<<"Numele fisierului de export:";
    string s;
    cin>>s;
    exportToHTML(s,ctr.getAllCourses());
}
//void ConsoleUI::replab(){
//    ctr.repolab();
//}
void ConsoleUI::contract_UI() {
    int cmd;
    int ok = 1;
    while (ok) {
        printContractMenu();
        cout << "Comanda este:";
        cin >> cmd;
        switch (cmd)
        {
            case 1:
                AddToContract_UI();
                break;
            case 2:
                AddRandom_UI();
                break;
            case 3:
                EmptyContract_UI();
                break;
            case 4:
                print(ctr.getAllCourses());
                break;
            case 5:
                ok = 0;
                break;
            case 6:
                exportCVS();
                break;
            case 7:
                exportHTML();
                break;
            case 8:
                raport();
                break;
            default:
                break;
        }
        cout<<'\n'<<"Total:"<<ctr.getAllCourses().size()<<'\n';

    }
}

void ConsoleUI::raport() {
    map<string,int>m = ctr.service_raport();
    for (auto itr = m.begin(); itr != m.end(); ++itr){
        cout<<itr->second<<"elemente de tip:\t"<<itr->first;
        cout<<'\n';
    }

}