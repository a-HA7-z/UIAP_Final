#include "Costumer.h"
using namespace std;
Costumer::Costumer(string fName,string lName, string IDNumber, int age)
            : User(fName,lName,IDNumber,age) {}

void Costumer::changeCardPin(int index,string newPin)
{
    CNode<unique_ptr<BankAccount>>* targetCard = BankAccounts.getHead();
    for(int i = 0;i < index;i++){
        targetCard = targetCard->getNext();
    }
    targetCard->getData()->setPIN(newPin);
}

void Costumer::changeCardStaticPass(int index, string newPassword)
{
    CNode<unique_ptr<BankAccount>>* targetCard = BankAccounts.getHead();
    for(int i = 0;i < index;i++){
        targetCard = targetCard->getNext();
    }
    targetCard->getData()->setStaticPassword(newPassword);
}