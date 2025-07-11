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

    void setPIN(const string& Pin);
    void setStaticPassword(const string& staticPass);
    void setDynamicPassword(const string& dynamicPass);
    void setBalance(long long int Balance);

    string getCardNumber() const;
    string getAccountNumber() const;
    string getIBANNumber() const;
    string getCVV2() const;
    string getExpDate() const;
    string getPIN() const;
    string getStaticPassword() const;
    string getDynamicPassword() const;
    long long int getBalance() const;

    void addMoney(long long int money);
};