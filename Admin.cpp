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
