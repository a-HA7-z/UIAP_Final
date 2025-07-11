#pragma once
template<typename T>
class CNode
{
private:
	T data;
	CNode<T>* next;
public:
	CNode(const T& Data, CNode<T>* Next) : data(Data), next(Next) {}

	T& getData() { return this->data; }

	CNode<T>* getNext() { return this->next; }

	void setNext(CNode<T>* Next)
	{
		this->next = Next;
	}
};