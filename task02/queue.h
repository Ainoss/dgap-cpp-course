#include <iostream>
#pragma once

template <typename data>
class BasicQueue
{
 public:
	 virtual ~BasicQueue();
	 virtual void enqueue(data) = 0;
	 virtual data dequeue() = 0;
	 virtual unsigned getLength() = 0;
};

template <typename data>
struct Element
{
	Element(data dat);
        data dat;
	Element *next;
};

template <typename data>
class ListQueue: public BasicQueue<data>
{
 public:
	    ListQueue();
	    ~ListQueue();
	    void enqueue(data dat);
	    data dequeue();
	    unsigned getLength();
	    
 private:
	    Element<data> *head;
	    Element<data> *tail;
	   
};

template <typename data>
class ArrayQueue: public BasicQueue<data>
{
 public:
	 ArrayQueue(unsigned max_size = 64);
	 ~ArrayQueue();
	 void enqueue(data dat);
	 data dequeue();
	 unsigned getLength();
 private:
	 unsigned size;
	 data *arr;
	 unsigned top;
};

template <typename data>
BasicQueue<data>::~BasicQueue()
{}

template <typename data>
Element<data>::Element(data dat): next(NULL), dat(dat)
{}

template <typename data>
ListQueue<data>::ListQueue(): tail(NULL), head(NULL)
{}

template <typename data>
ListQueue<data>::~ListQueue()
{
	while (head)
	{
		dequeue();
	}
}

template <typename data>
void ListQueue<data>::enqueue(data dat)
{
	if (head == NULL)
	{
		head = tail = new Element<data>(dat);
	}
	else 
	{
		tail->next = new Element<data>(dat);
		tail = tail->next;
	}
}

template <typename data>
data ListQueue<data>::dequeue()
{
	data ret;
	if (head == NULL)
	{
		std::cout << "Empty list" << std::endl;
		exit(1);
	}
	else
	{
		ret = head->dat;
		Element<data> *tmp = head;
		head = head->next;
		delete tmp;
	}
	return ret;
}

template <typename data>
unsigned ListQueue<data>::getLength()
{
	Element<data> *p = head;
	unsigned n;

	while (p != NULL)
	{
		p = p->next;
		++n;
	}
	return n;
}

template <typename data>
ArrayQueue<data>::ArrayQueue(unsigned max_size): size(max_size), top(0)
{
	arr = new data[max_size];
}

template <typename data>
ArrayQueue<data>::~ArrayQueue()
{
	delete arr;
}

template <typename data>
void ArrayQueue<data>::enqueue(data dat)
{
	if (top <= size - 2)
	{
	arr[top] = dat;
	top++;
	}
	else if (top == size - 1)
	{
		arr[top] = dat;
	}
	else
		std::cout << "Array is fool" << std::endl;
}

template <typename data>
data ArrayQueue<data>::dequeue()
{
	data x;
	if (top != 0 && top <= (size -1))
	{
		x = arr[top]; 
		arr[top] = 0;
		top--;
	}
	else if (top == 0)
	{
		std::cout << "Array is empty" << std::endl;
		exit(1);
	}
	else 
	{
		std::cout << "top za predelami array" << std::endl;
		exit(1);
	}       
	return (x);
}

template <typename data>
unsigned ArrayQueue<data>::getLength()
{
	return (top);
}




	







