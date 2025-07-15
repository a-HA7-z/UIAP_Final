#include "BankAccount.h"

BankAccount::BankAccount(const string& cardNumber, const string& accountNumber, const string& IBAN_number,
                         const string& CVV2, const string& Exp_Date, const string& PIN,
                         const string& staticPassword, long long int balance)
        : cardNumber(cardNumber), accountNumber(accountNumber), IBAN_number(IBAN_number), CVV2(CVV2),
          Exp_Date(Exp_Date), PIN(PIN), staticPassword(staticPassword),dynamicPassword(""),balance(balance) {}

void BankAccount::setPIN(const string& Pin) {
    PIN = Pin;
}
void BankAccount::setStaticPassword(const string& staticPass) {
    this->staticPassword = staticPass;
}
void BankAccount::setDynamicPassword(const string& dynamicPass) {
    this->dynamicPassword = dynamicPass;
}
void BankAccount::setBalance(long long int Balance) {
    this->balance = Balance;
}

string BankAccount::getCardNumber() const {
    return cardNumber;
}
string BankAccount::getAccountNumber() const {
    return accountNumber;
}
string BankAccount::getIBANNumber() const {
    return IBAN_number;
}
string BankAccount::getCVV2() const {
    return CVV2;
}
string BankAccount::getExpDate() const {
    return Exp_Date;
}
string BankAccount::getPIN() const {
    return PIN;
}
string BankAccount::getStaticPassword() const {
    return staticPassword;
}
long long int BankAccount::getBalance() const {
    return balance;
}
string BankAccount::getDynamicPassword() const {
    return dynamicPassword;
}

void BankAccount::addMoney(long long int money) {
    balance = balance + money;
}
