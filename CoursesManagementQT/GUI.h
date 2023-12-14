//
// Created by ultra on 08.06.2023.
//

#ifndef QTLAB_GUI_H
#define QTLAB_GUI_H
#include <qwidget.h>
#include <qlistwidget.h>
#include <qpushbutton.h>
#include <qlineedit.h>
#include <qboxlayout.h>
#include <qdebug.h>
#include "Headers/Service.h"
#include "Headers/Contract.h"
#include <vector>
#include <qlabel.h>
#include <map>
class contractGUI : public QWidget{
private:
    service& ctr;
    QHBoxLayout* lyMain = new QHBoxLayout;
    QListWidget* lst;
    QPushButton* btnSortByore;
    QPushButton* btnAddToCos;
    QPushButton* btnSortBytip;
    QPushButton* btnFiltrareOre;
    QPushButton* btnFiltrareProf;
    QLineEdit* txtdenumire;
    QLineEdit* txttip;
    QLineEdit* txtore;
    QLineEdit* txtprofesor;
    QPushButton* btnAdd;
    QPushButton* btnModify;
    QPushButton* btnDelete;
    QPushButton* btnundo;
    QVBoxLayout* lyBtnDy = new QVBoxLayout;
    QWidget* btnDyn = new QWidget;
    void initGUICmps();
    void reloadList(const std::vector<contract>& all);
    void connectSignalsSlots();
    void addNew();
    void adaugaButoane(const std::vector<contract>& all);
    void adaugadacatip(const contract& c);
    void Modify();
    void Delete();
    void undo();
    void clearLayout(QLayout *layout);
    map<QPushButton*,int> butoanedinamice;
public:
    contractGUI(service& ctr) :ctr{ ctr } {
        initGUICmps();
        connectSignalsSlots();
        reloadList(ctr.getall());
    }
};




#endif //QTLAB_GUI_H
