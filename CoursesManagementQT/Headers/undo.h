//
// Created by ultra on 06.06.2023.
//

#ifndef QTLAB_UNDO_H
#define QTLAB_UNDO_H
#include "Contract.h"
#include "Repo.h"
class ActiuneUndo {
public:
    virtual void doUndo() = 0;
    //destructorul e virtual pentru a ne asigura ca daca dau delete se apeleaza destructorul din clasa care trebuie
    virtual ~ActiuneUndo()= default;
};

class UndoAdauga : public ActiuneUndo {
    contract addedcontract;
    repo& rep;
public:
    UndoAdauga(repo& rep,const  contract& p) :rep{ rep }, addedcontract{ p } {}
    void doUndo() override {
        rep.delete_contract(addedcontract.get_denumire());
    }
};

class UndoSterge : public ActiuneUndo {
    contract addedcontract;
    repo& rep;
public:
    UndoSterge(repo& rep, const  contract& p) :rep{ rep }, addedcontract{ p } {}
    void doUndo() override {
        rep.store(addedcontract);
    }
};
class UndoModifica : public ActiuneUndo {
    contract c;
    repo& rep;
public:
    UndoModifica(repo& rep, const  contract& p) :rep{ rep }, c{ p } {}
    void doUndo() override {
        rep.modify_contract(c.get_denumire(),c.get_ore(),c.get_tip(),c.get_profesor());
    }
};
#endif //QTLAB_UNDO_H
