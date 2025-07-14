#pragma once
#include "BankAccount.h"
using namespace std;

class CurrentAccount : public BankAccount
{
public:
    CurrentAccount(const string& cardNumber, const string& accountNumber, const string& IBAN_number,
                   const string& CVV2, const string& Exp_Date, const string& PIN,
                   const string& staticPassword, long long int balance);

    void issueCheque();

    void showType();
};
