#pragma once
#include <iostream>
#include <memory>
#include "User.h"
#include "BankAccount.h"
#include "CLinkedList.h"
using namespace std;

class Costumer : public User
{
    friend class Admin;

private:
    CLinkedList<shared_ptr<BankAccount>> BankAccounts;
public:
    Costumer(string fName,string lName,string IDNumber,int age);

    Costumer(const Costumer& other);

    void changeCardPin(int ,string );

    void changeCardStaticPass(int , string);

    void cardToCard(string originCard,BankAccount* destinationCard,long long int money);
};
