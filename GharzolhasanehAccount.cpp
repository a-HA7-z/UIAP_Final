#include "iostream"
#include "GharzolhasanehAccount.h"

GharzolhasanehAccount::GharzolhasanehAccount(const string& cardNumber, const string& accountNumber, const string& IBAN_number,
                                             const string& CVV2, const string& Exp_Date, const string& PIN,
                                             const string& staticPassword, long long int balance) :
        BankAccount(cardNumber,accountNumber,IBAN_number,CVV2,Exp_Date,PIN,staticPassword,balance) {}

void GharzolhasanehAccount::applyForLoan() {
    cout << "Applying for Gharzolhasaneh loan..." << endl;
}