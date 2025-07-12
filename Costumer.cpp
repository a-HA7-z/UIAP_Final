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

void Costumer::cardToCard(string originCard, BankAccount *destinationCard, long long int money) {
    CNode<unique_ptr<BankAccount>>* targetOriginCard = BankAccounts.getHead();
    for(int i = 0;i < BankAccounts.getSize();i++){
        if(targetOriginCard->getData()->getCardNumber() == originCard){
            break;
        }
        targetOriginCard = targetOriginCard->getNext();
    }
    targetOriginCard->getData()->addMoney(-1*money);

    destinationCard->addMoney(money);
}
