#include "ProjectData.h"

ProjectData::ProjectData(){
    Admin defaultAdmin("admin","default","1234567890",20);
    defaultAdmin.setUsername("aduser");
    defaultAdmin.setPassword("adpass");
    addAdmin(defaultAdmin);

    Costumer defaultCostumer("costumer","default","9876543210",20);
    defaultCostumer.setUsername("couser");
    defaultCostumer.setPassword("copass");
    addCostumer(defaultCostumer);

    Costumer& customerRef = getCostumers().getHead()->getData();
    defaultAdmin.createBankAccount(customerRef,0,"5859585958595859","9876543210","IR1005859",
                                    "1111","07/07","1111","1111",700000);

    addBankAccount(customerRef.getBankAccounts().getTail()->getData());
}

ProjectData& ProjectData::data() {
    static ProjectData instance;
    return instance;
}

void ProjectData::addAdmin(const Admin& admin) {
    admins.listPushBack(admin);
}
void ProjectData::addCostumer(const Costumer& costumer) {
    costumers.listPushBack(costumer);
}
void ProjectData::addBankAccount(std::shared_ptr<BankAccount> account) {
    bankAccounts.listPushBack(account);
}

CLinkedList<Admin>& ProjectData::getAdmins() {
    return admins;
}

CLinkedList<Costumer>& ProjectData::getCostumers() {
    return costumers;
}

CLinkedList<std::shared_ptr<BankAccount>>& ProjectData::getBankAccounts() {
    return bankAccounts;
}

Admin* ProjectData::findAdmin(const std::string& username) {
    CNode<Admin>* current = admins.getHead();
    while (current != nullptr) {
        if (current->getData().getUsername() == username) {
            return &current->getData();
        }
        current = current->getNext();
    }
    return nullptr;
}

Costumer* ProjectData::findCostumer(const std::string& username) {
    CNode<Costumer>* current = costumers.getHead();
    while (current != nullptr) {
        if (current->getData().getUsername() == username) {
            return &current->getData();
        }
        current = current->getNext();
    }
    return nullptr;
}

std::shared_ptr<BankAccount> ProjectData::findBankAccount(const std::string& cardNumber) {
    CNode<std::shared_ptr<BankAccount>>* current = bankAccounts.getHead();
    while (current != nullptr) {
        if (current->getData()->getCardNumber() == cardNumber) {
            return current->getData();
        }
        current = current->getNext();
    }
    return nullptr;
}
