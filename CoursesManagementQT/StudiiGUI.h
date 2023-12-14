//
// Created by ultra on 09.06.2023.
//
#ifndef QTLAB_STUDIIGUI_H
#define QTLAB_STUDIIGUI_H
#include <qwidget.h>
#include <QWidget>
#include "Headers/Studii.h"
#include <qlistwidget.h>
#include <qlayout.h>
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
#include <QTableWidget>
#include <map>
#include <QHeaderView>
#include <QGroupBox>
#include <QRadioButton>
#include "Headers/export.h"
class CosGUI : public QWidget {
private:
    contract_studii& cos;
    void initGUIcmps();
    void connectSignalsSlots();
    void reloadList(const vector<contract>& alll);

    QVBoxLayout* mainLayout = new QVBoxLayout;
    QTableWidget* table;
    QListWidget* cWidget = new QListWidget;

    QGroupBox* groupBox = new QGroupBox(tr("Tip export"));
    QRadioButton* radioexpHTML = new QRadioButton(QString::fromStdString("HTML"));
    QRadioButton* radioexpCCV = new QRadioButton(QString::fromStdString("CCV"));
    QPushButton* btnexp;
public:
    CosGUI(contract_studii& c) : cos{ c } {
        initGUIcmps();
        connectSignalsSlots();
        reloadList(cos.getallcourses());
    }
};
#endif //QTLAB_STUDIIGUI_H
