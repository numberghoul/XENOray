#pragma once
#include "Node.h"
#include "../E_Def.h"

template <class T>
class List
{
public:
	List<T>()
	{
		mpHead = nullptr;
		mpTail = nullptr;
		mCount = 0;
	}

	int size() const { return mCount; }

	Node<T> *getHead() const { return mpHead; }

	void print()
	{
		Node<T> *item = mpHead;

		while (item != nullptr)
		{
			std::cout << item->getData() << " ";
			item = item->getNext();
		}

		std::cout << std::endl;
	}

	void printReverse()
	{
		Node<T> *item = mpTail;

		while (item != nullptr)
		{
			std::cout << item->getData() << " ";
			item = item->getPrev();
		}

		std::cout << std::endl;
	}

	bool isEmpty()
	{
		return mpHead == nullptr;
	}

	void insertAtFront(T data)
	{
		Node<T> *newHead = new Node<T>(data);

		if (mpHead == nullptr)
		{
			mpTail = newHead;
		}
		else
		{
			newHead->setNext(mpHead);
			mpHead->setPrev(newHead);
		}
		mCount++;

		mpHead = newHead;
	}

	void insertAtEnd(T data)
	{
		Node<T> *newTail = new Node<T>(data);

		if (mpTail == nullptr)
		{
			mpHead = newTail;
		}
		else
		{
			newTail->setPrev(mpTail);
			mpTail->setNext(newTail);
		}
		mCount++;

		mpTail = newTail;
	}

	bool deleteFromFront()
	{
		Node<T> *newHead = mpHead->getNext();

		if (mpHead == nullptr)
			return false;

		if (newHead != nullptr)
		{
			mpHead->setNext(nullptr);
			newHead->setPrev(nullptr);
		}
		delete mpHead;

		mpHead = newHead;
		if (mpHead == nullptr)
			mpTail = newHead;
		mCount--;

		return true;
	}

	bool deleteFromEnd()
	{
		Node<T> *newTail = mpTail->getPrev();

		if (mpTail == nullptr)
			return false;

		if (newTail != nullptr)
		{
			mpTail->setPrev(nullptr);
			newTail->setNext(nullptr);
		}
		delete mpTail;

		mpTail = newTail;
		if (mpTail == nullptr)
			mpHead = newTail;
		mCount--;

		return true;
	}

	bool deleteAt(int index)
	{
		Node<T> *curNode = mpHead, *prevNode, *nextNode;

		for (int i = 0; i < index && curNode != nullptr; ++i)
			curNode = curNode->getNext();

		if (curNode == nullptr)
			return false;

		prevNode = curNode->getPrev();
		nextNode = curNode->getNext();

		if (prevNode == nullptr)
			return deleteFromFront();
		else if (nextNode == nullptr)
			return deleteFromEnd();

		curNode->setNext(nullptr);
		curNode->setPrev(nullptr);

		prevNode->setNext(nextNode);
		nextNode->setPrev(prevNode);

		delete curNode;
		mCount--;

		return true;
	}

	T &operator[](int index)
	{
		Node<T> *curNode = mpHead;
		for (int i = 0; i < index && curNode != nullptr; ++i)
			curNode = curNode->getNext();

		if (curNode == nullptr)
		{
			std::string ex = "Data does not exist at index " + std::to_string(index);
			throw std::out_of_range(ex);
		}

		return curNode->getData();
	}

private:
	Node<T> *mpHead,
			*mpTail;
	int mCount;
};
