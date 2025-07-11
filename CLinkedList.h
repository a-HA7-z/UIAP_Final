#pragma once
#include <iostream>
#include "CNode.h"
class CLinkedList
{
private:
	CNode* head;
	int size;
	CNode* tail;
public:
	CLinkedList()
	{
        this->head = nullptr;
        this->tail = nullptr;
        size = 0;
	}

    CLinkedList(CLinkedList& a):
            head(nullptr), tail(nullptr), size(0)
    {
        CNode* tmp = a.head;
        for (int i = 0 ; i < a.size; i++)
        {
            this->listPushBack(tmp->getData());
            tmp = tmp->getNext();
        }
    }

	// void setHead(CNode* head) { this->head = head; }
	// void setTail(CNode* tail) { this->tail = tail; }
	
	void listPushBack( int data)
	{
		CNode* tmp = new CNode;
		tmp->setData(data);
		tmp->setNext(nullptr);
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

	void printList()
	{
		CNode* tmp = head;
		while (tmp != nullptr)
		{
			std::cout << tmp->getData() << '\t';
			tmp = tmp->getNext();	
		}
	}

	~CLinkedList()
	{
		std::cerr << "An object is dying\n";
		CNode* tmp = this->head;
		CNode* tmp2;
		for (int i = 0; i < this->size;i++)
		{
			tmp2 = tmp->getNext();
			delete tmp;
			tmp = tmp2;
		
		}
		this->size = 0;
		return;
	}
};

