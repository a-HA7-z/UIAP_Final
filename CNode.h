#pragma once
class CNode
{
private:
	int data;
	CNode* next;
public:
	int getData() { return this->data; }
	CNode* getNext() { return this->next; }
	
	void setData(int Data)
	{
		 this->data = Data;
	}

	void setNext(CNode* Next)
	{
		this->next = Next;
	}
};