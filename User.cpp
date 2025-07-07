#include "User.h"

User::User(std::string fName, std::string lName, std::string IDNumber, int Age) :firstName(fName),lastName(lName),
            nationalCode(IDNumber), age(Age) {}

void User::setUsername(string uname) {
    username = uname;
}

void User::setPassword(string pass) {
    password = pass;
}

string User::getFirstName() const {
    return firstName;
}

string User::getLastName() const {
    return lastName;
}

string User::getNationalCode() const {
    return nationalCode;
}

int User::getAge() const {
    return age;
}

string User::getUsername() const{
    return username;
}

string User::getPassword() const{
    return password;
}