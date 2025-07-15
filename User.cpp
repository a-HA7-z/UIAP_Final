#include "User.h"

User::User(std::string fName, std::string lName, std::string IDNumber, int Age) :firstName(fName),lastName(lName),
            nationalCode(IDNumber), age(Age) {}

User::User(const User& other): firstName(other.firstName),lastName(other.lastName),
    nationalCode(other.nationalCode),age(other.age),
    username(other.username),password(other.password) {}

void User::setUsername(string uname) {
    username = uname;
}

void User::setPassword(string pass) {
    password = pass;
}

void User::setFirstName(string name) {
    firstName = name;
}

void User::setLastName(string name) {
    lastName = name;
}

void User::setNationalCode(string code) {
    nationalCode = code;
}

void User::setAge(int Age) {
    this->age = Age;
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
