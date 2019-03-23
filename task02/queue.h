
#pragma once

typedef int data;
struct List
{
	List *next;
	data *Data;
};

class BasicQueue
{
public:

	// Add element to the end
	virtual void enqueue(data &) = 0;

	// Return first element
	virtual data dequeue() = 0;

	// Get total count of elements
	virtual unsigned getLength() = 0;

};

class ListQueue: public BasicQueue
{
public:
	ListQueue();
	~ListQueue();
	void enqueue(data &d);
	data dequeue();
	unsigned getLength();
private:
	List* list;
	List* new_l();
	void del_l(List* l);
};

class ArrayQueue: public BasicQueue
{
public:
	ArrayQueue(unsigned max_size = 64);
	~ArrayQueue();
	void enqueue(data &d);
	data dequeue();
	unsigned getLength();
private:
	unsigned first;
	unsigned last;
	unsigned max_len;
	data* array;
};

