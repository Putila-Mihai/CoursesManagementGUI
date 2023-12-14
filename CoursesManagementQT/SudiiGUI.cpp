#include "StudiiGUI.h"
#include <qtimer.h>
void CosGUI::initGUIcmps() {
    QHBoxLayout* lyMain = new QHBoxLayout;
    this->setLayout(lyMain);
    //right
    QWidget* right = new QWidget;
    QVBoxLayout* lyright = new QVBoxLayout;
    right->setLayout(lyright);

    QVBoxLayout* lyRadioBox = new QVBoxLayout;
    this->groupBox->setLayout(lyRadioBox);
    lyRadioBox->addWidget(radioexpHTML);
    lyRadioBox->addWidget(radioexpCCV);

    btnexp = new QPushButton("Exporta contratul");
    lyRadioBox->addWidget(btnexp);

    lyright->addWidget(groupBox);


    //left
    QWidget* left = new QWidget;
    QVBoxLayout* lyleft = new QVBoxLayout;
    left->setLayout(lyleft);

    int noLines = 13;
    int noColumns = 4;
    this->table = new QTableWidget{noLines, noColumns};
    QStringList tblHeaderList;
    tblHeaderList << "denumire" << "Tip" << "Ore" << "Profesor";
    this->table->setHorizontalHeaderLabels(tblHeaderList);
    //redimensionare
    this->table->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    lyleft->addWidget(table);

    lyMain->addWidget(left);
    lyMain->addWidget(right);
}
void CosGUI::connectSignalsSlots() {
    QTimer* refreshTimer = new QTimer;
    QObject::connect(refreshTimer, &QTimer::timeout, [this]() {
        reloadList(cos.getallcourses());
    });
    refreshTimer->start(1000);

    QObject::connect(btnexp, &QPushButton::clicked, [&]() {
        if (this->radioexpHTML->isChecked())
            exportToHTML("textExport.html",cos.getallcourses());
        else if (this->radioexpCCV->isChecked())
            exportToCVS("textExport.ccv",cos.getallcourses());
    });

}
void CosGUI::reloadList(const vector<contract>& alll) {
    this->table->clearContents();
    this->table->setRowCount(alll.size());
    int lineNumber = 0;
    for (auto& c : alll) {
        this->table->setItem(lineNumber, 0, new QTableWidgetItem(QString::fromStdString(c.get_denumire())));
        this->table->setItem(lineNumber, 1, new QTableWidgetItem(QString::fromStdString(c.get_tip())));
        this->table->setItem(lineNumber, 2, new QTableWidgetItem(QString::number(c.get_ore())));
        this->table->setItem(lineNumber, 3, new QTableWidgetItem(QString::fromStdString(c.get_profesor())));
        lineNumber++;
    }
}