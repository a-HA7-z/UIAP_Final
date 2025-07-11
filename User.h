#include <iostream>
using namespace std;

class User
{
private:
    string firstName;
    string lastName;
    string nationalCode;
    int age;
    string username;
    string password;
public:
    User(string fName,string lName,string IDNumber,int age);

    void setUsername(string);
    void setPassword(string);
    void setFirstName(string);
    void setLastName(string);
    void setNationalCode(string);
    void setAge(int);

    string getFirstName() const;
    string getLastName() const;
    string getNationalCode() const;
    int getAge() const;
    string getUsername() const;
    string getPassword() const;
};