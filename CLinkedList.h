#pragma once
#include <iostream>
#include "CNode.h"

template<typename T>
class CLinkedList
{
private:
    CNode<T>* head;
    int size;
    CNode<T>* tail;

public:
    CLinkedList()
    {
        this->head = nullptr;
        this->tail = nullptr;
        size = 0;
    }

    CLinkedList(CLinkedList<T>& a):
            head(nullptr), tail(nullptr), size(0)
    {
        CNode<T>* tmp = a.head;
        for (int i = 0 ; i < a.size; i++)
        {
            this->listPushBack(tmp->getData());
            tmp = tmp->getNext();
        }
    }

    void listPushBack(T data)
    {
        CNode<T>* tmp = new CNode<T>(data, nullptr);
        if (this->tail == nullptr)
        {
            this->head = tmp;
            this->tail = tmp;
            size++;
        }
        else
        {
            this->tail->setNext(tmp);
            this->tail = tmp;
            this->size++;
        }
    }

    void deleteNodeAt(int index)
    {
        if (index < 0 || index >= size) {
            return;
        }

        CNode<T>* current = head;
        CNode<T>* previous = nullptr;

        for (int i = 0; i < index; i++)
        {
            previous = current;
            current = current->getNext();
        }

        if (previous == nullptr)
        {
            head = current->getNext();
            if (head == nullptr) {
                tail = nullptr;
            }
        }
        else
        {
            previous->setNext(current->getNext());
            if (current == tail) {
                tail = previous;
            }
        }

        delete current;
        size--;
    }

    void printList()
    {
        CNode<T>* tmp = head;
        while (tmp != nullptr)
        {
            std::cout << tmp->getData() << '\t';
            tmp = tmp->getNext();
        }
    }

    ~CLinkedList()
    {
        CNode<T>* tmp = this->head;
        CNode<T>* tmp2;
        while (tmp != nullptr)
        {
            tmp2 = tmp->getNext();
            delete tmp;
            tmp = tmp2;
        }
        this->head = nullptr;
        this->tail = nullptr;
        this->size = 0;
    }
};