#include "Node.h"

template <class T>
class List
{
public:
	List<T>()
	{
		mpHead = nullptr;
		mpTail = nullptr;
	}

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

		mpHead = newHead;
	}

	void insertAtEnd(T data)
	{
		Node<T> *newTail = new Node<T>(data);

		if (mpTail == nullptr)
		{
			mpTail = newTail;
		}
		else
		{
			newTail->setPrev(mpTail);
			mpTail->setNext(newTail);
		}

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

		return true;
	}

private:
	Node<T> *mpHead,
				*mpTail;
};
