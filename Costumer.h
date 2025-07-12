#include <iostream>
#include <memory>
#include "User.h"
#include "BankAccount.h"
#include "CLinkedList.h"
using namespace std;

class Costumer : User
{
private:
    CLinkedList<unique_ptr<BankAccount>> BankAccounts;
public:
    Costumer(string fName,string lName,string IDNumber,int age);
};