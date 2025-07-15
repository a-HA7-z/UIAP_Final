#include <iostream>
#include "CurrentAccount.h"

CurrentAccount::CurrentAccount(const string& cardNumber, const string& accountNumber, const string& IBAN_number,
                               const string& CVV2, const string& Exp_Date, const string& PIN,
                               const string& staticPassword, long long int balance) :
                               BankAccount(cardNumber,accountNumber,IBAN_number,CVV2,Exp_Date,PIN,staticPassword,balance) {}

void CurrentAccount::issueCheque() {
    cout << "Issuing a cheque from current account..." << endl;
}

string CurrentAccount::showType() {
    return "CurrentAccount";
}
