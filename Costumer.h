#include <iostream>
#include <memory>
#include "User.h"
#include "BankAccount.h"
#include "CLinkedList.h"
using namespace std;

class Costumer : public User
{
private:
    CLinkedList<unique_ptr<BankAccount>> BankAccounts;
public:
    Costumer(string fName,string lName,string IDNumber,int age);

    void changeCardPin(int ,string );

    void changeCardStaticPass(int , string);

    void cardToCard(string originCard,BankAccount* destinationCard,long long int money);
};