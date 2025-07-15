#pragma once
#include "User.h"
#include "Costumer.h"
#include "CLinkedList.h"
#include "CurrentAccount.h"
#include "DepositAccount.h"
#include "GharzolhasanehAccount.h"
class Admin : public User
{
public:
    Admin(string fName,string lName,string IDNumber,int age);
    Admin(const Admin &other);

    void addCostumer(CLinkedList<Costumer>& list,string fName,string lName,string IDNumber,int age,string user,string password);

    void deleteCostumer(CLinkedList<Costumer>& costumers,int index);

    void createBankAccount(Costumer& costumer,int type,
                           const string& cardNumber, const string& accountNumber, const string& IBAN_number,
                           const string& CVV2, const string& Exp_Date, const string& PIN,
                           const string& staticPassword, long long int balance);
};
