#pragma once
#include "BankAccount.h"
using namespace std;

class DepositAccount : public BankAccount
{
public:
    DepositAccount(const string& cardNumber, const string& accountNumber, const string& IBAN_number,
                   const string& CVV2, const string& Exp_Date, const string& PIN,
                   const string& staticPassword, long long int balance);

    double calculateInterest(int );

    virtual void showType();
};
