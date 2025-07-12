cmake_minimum_required(VERSION 3.30)
project(UIAP_Final)

set(CMAKE_CXX_STANDARD 20)

add_executable(UIAP_Final
        main.cpp
        User.cpp
        Admin.cpp
        Costumer.cpp
        BankAccount.cpp
        CurrentAccount.cpp
        DepositAccount.cpp
        GharzolhasanehAccount.cpp
        CLinkedList.h
        CNode.h
)
