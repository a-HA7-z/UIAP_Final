#pragma once
#include <string>
using namespace std;
class BankAccount
{
private:
    string cardNumber;
    string accountNumber;
    string IBAN_number;
    string CVV2;
    string Exp_Date;
    string PIN;
    string staticPassword;
    string dynamicPassword;
    long long int balance;
public:
    BankAccount(const string& cardNumber, const string& accountNumber, const string& IBAN_number,
                const string& CVV2, const string& Exp_Date, const string& PIN,
                const string& staticPassword, long long int balance);

    virtual void setPIN(const string& Pin);
    virtual void setStaticPassword(const string& staticPass);
    virtual void setDynamicPassword(const string& dynamicPass);
    virtual void setBalance(long long int Balance);

    virtual string getCardNumber() const;
    virtual string getAccountNumber() const;
    virtual string getIBANNumber() const;
    virtual string getCVV2() const;
    virtual string getExpDate() const;
    virtual string getPIN() const;
    virtual string getStaticPassword() const;
    virtual string getDynamicPassword() const;
    virtual long long int getBalance() const;

    virtual void addMoney(long long int money);

    virtual string showType() = 0;
};
