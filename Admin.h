#include "User.h"
#include "Costumer.h"
#include "CLinkedList.h"
class Admin : public User
{
public:
    Admin(string fName,string lName,string IDNumber,int age);

    void addCostumer(CLinkedList<Costumer>& list,string fName,string lName,string IDNumber,int age,string user,string password);
};