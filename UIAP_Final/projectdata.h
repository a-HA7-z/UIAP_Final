#pragma once
#ifndef PROJECTDATA_H
#define PROJECTDATA_H

#include "../Admin.h"
#include "../Costumer.h"
#include "../BankAccount.h"
#include "../CLinkedList.h"
#include <memory>
#include <string>

class ProjectData {
private:
    CLinkedList<Admin> admins;
    CLinkedList<Costumer> costumers;
    CLinkedList<std::shared_ptr<BankAccount>> bankAccounts;

    ProjectData();

public:   
    static ProjectData& data();

    void addAdmin(const Admin& admin);
    void addCostumer(const Costumer& costumer);
    void addBankAccount(std::shared_ptr<BankAccount> account);

    CLinkedList<Admin>& getAdmins();
    CLinkedList<Costumer>& getCostumers();
    CLinkedList<std::shared_ptr<BankAccount>>& getBankAccounts();

    Admin* findAdmin(const std::string& username);
    Costumer* findCostumer(const std::string& username);
    std::shared_ptr<BankAccount> findBankAccount(const std::string& cardNumber);
};

#endif // PROJECTDATA_H
