#include "GUI.h"
#include "Headers/Contract.h"
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMessageBox>
#include <qpalette.h>
#include <qbrush.h>
#include<qdebug.h>
#include <string>
#include <algorithm>
void contractGUI::initGUICmps() {
    setLayout(lyMain);
    QWidget* widDreapta = new QWidget;
    QVBoxLayout* vl = new QVBoxLayout;
    widDreapta->setLayout(vl);
    lst = new QListWidget;
    vl->addWidget(lst);

    QWidget* widBtnDreapta = new QWidget;
    QHBoxLayout* lyBtnsDr = new QHBoxLayout;

    widBtnDreapta->setLayout(lyBtnsDr);
    btnSortByore = new QPushButton("Sort ore");
    lyBtnsDr->addWidget(btnSortByore);

    btnAddToCos = new QPushButton("adauga la contract");
    lyBtnsDr->addWidget(btnAddToCos);

    btnSortBytip = new QPushButton("Sort profesor");
    lyBtnsDr->addWidget(btnSortBytip);

    btnFiltrareOre = new QPushButton("Filtru ore");
    lyBtnsDr->addWidget(btnFiltrareOre);
    btnFiltrareProf = new QPushButton("Filtru Profesor");
    lyBtnsDr->addWidget(btnFiltrareProf);
    vl->addWidget(widBtnDreapta);

    lyMain->addWidget(widDreapta);

    //fac un form pentru detalii
    QWidget* widDetalii = new QWidget;
    QFormLayout* formLDetalii = new QFormLayout;
    widDetalii->setLayout(formLDetalii);
    txtdenumire = new QLineEdit;
    formLDetalii->addRow(new QLabel("denumire: "),txtdenumire);
    txttip = new QLineEdit;
    formLDetalii->addRow(new QLabel("Tip: "), txttip);
    txtore = new QLineEdit;
    formLDetalii->addRow(new QLabel("Ore: "), txtore);
    txtprofesor = new QLineEdit;
    formLDetalii->addRow(new QLabel("Profesor: "), txtprofesor);

    btnAdd = new QPushButton("Adauga Curs:");
    btnModify = new QPushButton("Modifica Curs:");
    btnDelete = new QPushButton("Sterge curs");
    btnundo = new QPushButton("UNDO");


    formLDetalii->addWidget(btnAdd);
    formLDetalii->addWidget(btnModify);
    formLDetalii->addWidget(btnDelete);
    formLDetalii->addWidget(btnundo);
    lyMain->addWidget(widDetalii);


    btnDyn->setLayout(lyBtnDy);
    lyMain->addWidget(btnDyn);


}

void contractGUI::reloadList(const std::vector<contract> &all) {
    lst->clear();
    for (const auto& p : all) {
        QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(p.get_denumire()));
        item->setData(Qt::UserRole, QString::fromStdString(p.get_tip()));
        if (p.get_ore() >= 25) {
            item->setData(Qt::BackgroundRole, QBrush{ Qt::darkMagenta, Qt::SolidPattern });
        }
        else
        if (p.get_ore() > 12)
            item->setData(Qt::BackgroundRole,QBrush{Qt::darkCyan,Qt::SolidPattern});
        lst->addItem(item);

    }
    clearLayout(lyBtnDy);
    adaugaButoane(ctr.getall());
//    while(!lyBtnDy->isEmpty())
//    {
//        lyBtnDy->removeItem(lyBtnDy->takeAt(0));
//    }
//    adaugaButoane(ctr.getall());
//    for(const auto& b : butoanedinamice)
//    {
//        contract c =ctr.search_s(b.first->text().toStdString());
//        if(c.get_tip()!="Info");
//        qDebug() <<1<<' ';
//        lyBtnDy->removeWidget(b.first);
//        butoanedinamice.erase(b.first);
//    }
}
void contractGUI::connectSignalsSlots() {
    //buton sort ore
    QObject::connect(btnSortByore, &QPushButton::clicked, [&]() {
        reloadList(ctr.sort_ore());
    });
    //buton sort tip si profesor
    QObject::connect(btnSortBytip, &QPushButton::clicked, [&]() {
        reloadList(ctr.sort_tip_prof());
    });
    QObject::connect(btnFiltrareOre, &QPushButton::clicked, [&]() {
        reloadList(ctr.filter_greater(txtore->text().QString::toInt()));
    });
    QObject::connect(btnFiltrareProf, &QPushButton::clicked, [&]() {
        reloadList(ctr.filter_teacher(txtprofesor->text().QString::toStdString()    ));
    });
    //buton pentru adaugare
    QObject::connect(btnAdd, &QPushButton::clicked, this, &contractGUI::addNew);
    //buton sterge
    QObject::connect(btnModify, &QPushButton::clicked, this, &contractGUI::Modify);
    //delete
    QObject::connect(btnDelete, &QPushButton::clicked, this, &contractGUI::Delete);
    //undo
    QObject::connect(btnundo, &QPushButton::clicked, this, &contractGUI::undo);


    //pentru lista
    QObject::connect(lst, &QListWidget::itemSelectionChanged, [&]() {
        auto sel = lst->selectedItems();
        if (sel.isEmpty()) {
            txtdenumire->setText("");
            txttip->setText("");
            txtore->setText("");
            txtprofesor->setText("");
            btnAddToCos->setDisabled(true);
        }
        else {
            auto selItem = sel.at(0);
            auto denumire = selItem->text();
            auto c = ctr.search_s(denumire.toStdString());
            txtdenumire->setText(denumire);
            txtore->setText(QString::number(c.get_ore()));
            txtprofesor->setText(QString::fromStdString(c.get_profesor()));
            txttip->setText(QString::fromStdString(c.get_tip()));
            btnAddToCos->setEnabled(true);
        }
    });

    QObject::connect(btnAddToCos, &QPushButton::clicked, this, [&]() {
        auto sel = lst->selectedItems();
        try {
            if (!sel.isEmpty()) {
                auto selItem = sel.at(0);
                auto denumire = selItem->text();
                ctr.addToContract(denumire.toStdString());
            }
        }
        catch (const ValidateException& ex) {
            QMessageBox::warning(this, "Warning", "QString::fromStdString(ex.getErrorMessages())");
        }
    });

}

void contractGUI::addNew() {
    try {
        ctr.addcontract(txtdenumire->text().toStdString(), txtore->text().toInt(), txttip->text().toStdString(),txtprofesor->text().toStdString());
        adaugadacatip(ctr.search_s(txtdenumire->text().toStdString()));
        reloadList(ctr.getall());
    }
    catch (ValidateException& ex) {
        QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getErrorMessages()));
    }
}

void contractGUI::Modify() {
    try{
        ctr.modify_s(txtdenumire->text().toStdString(), txtore->text().toInt(), txttip->text().toStdString(),txtprofesor->text().toStdString());
        reloadList(ctr.getall());
    }
    catch (RepoException& ex){
        QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getErrorMessage()));
    }
}
void contractGUI::Delete() {
    try{
        ctr.delete_s(txtdenumire->text().toStdString());
        reloadList(ctr.getall());
    }
    catch (RepoException& ex){
        QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getErrorMessage()));
    }
}
void contractGUI::adaugadacatip(const contract &c) {
    if (c.get_tip() == "Info") {
        auto btn = new QPushButton{ QString::fromStdString(c.get_denumire()) };
//        butoanedinamice.insert({btn,c.get_ore()});
        lyBtnDy->addWidget(btn);
        QObject::connect(btn, &QPushButton::clicked, [this, btn, c]() {
            QMessageBox::information(nullptr, "Info", "Numar Ore: "+QString::number(c.get_ore()));
            delete btn;
        });
    }
}
void contractGUI::adaugaButoane(const std::vector<contract>& all) {
    for (const auto& c : all) {
        adaugadacatip(c);
    }

}
void contractGUI::undo(){
    try {
        ctr.undo();
        reloadList(ctr.getall());
    }
    catch (std::exception& ex)
    {
        QMessageBox::warning(this, "Warning", QString::fromStdString(ex.what()));
    }

}

void contractGUI::clearLayout(QLayout *layout) {
    if (layout == NULL)
        return;
    QLayoutItem *item;
    while((item = layout->takeAt(0))) {
        if (item->layout()) {
            clearLayout(item->layout());
            delete item->layout();
        }
        if (item->widget()) {
            delete item->widget();
        }
        delete item;
    }
}