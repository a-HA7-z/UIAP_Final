#include <iostream>
#include "DepositAccount.h"

DepositAccount::DepositAccount(const string& cardNumber, const string& accountNumber, const string& IBAN_number,
                               const string& CVV2, const string& Exp_Date, const string& PIN,
                               const string& staticPassword, long long int balance) :
        BankAccount(cardNumber,accountNumber,IBAN_number,CVV2,Exp_Date,PIN,staticPassword,balance) {}

double DepositAccount::calculateInterest(int months) {
    double rate = 0.1;
    return (getBalance() * rate * months) / 12.0;
}

void DepositAccount::showType() {
    std::cout << "Deposit Bank Account" << endl;
}
