#include <iostream>
#include "Admin.h"

using namespace std;

Admin::Admin(string fName, string lName,string IDNumber, int age)
            : User(fName,lName,IDNumber,age){}

void Admin::addCostumer(CLinkedList<Costumer>& list, string fName, string lName, string IDNumber, int age, string user, string password) {
    Costumer newCostumer(fName,lName,IDNumber,age);
    newCostumer.setUsername(user);
    newCostumer.setPassword(password);
    list.listPushBack(newCostumer);
}

void Admin::deleteCostumer(CLinkedList<Costumer> &costumers, int index) {
    costumers.deleteNodeAt(index);
}

void Admin::createBankAccount(Costumer &costumer, int type,
                              const string &cardNumber, const string &accountNumber,
                              const string &IBAN_number, const string &CVV2, const string &Exp_Date, const string &PIN,
                              const string &staticPassword, long long int balance)
{
    if(costumer.BankAccounts.getSize() == 5) { return; }

    if(type == 0){
        costumer.BankAccounts.listPushBack(make_shared<CurrentAccount>(cardNumber,accountNumber,IBAN_number,CVV2,Exp_Date,PIN,staticPassword,balance));
    }

    if(type == 1){
        costumer.BankAccounts.listPushBack(make_shared<DepositAccount>(cardNumber,accountNumber,IBAN_number,CVV2,Exp_Date,PIN,staticPassword,balance));
    }

    if(type == 2){
        costumer.BankAccounts.listPushBack(make_shared<GharzolhasanehAccount>(cardNumber,accountNumber,IBAN_number,CVV2,Exp_Date,PIN,staticPassword,balance));
    }
}
