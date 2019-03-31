#include <cstdlib>
#include <iostream>

#pragma once

//----------------------------------------------------

template <typename data>
struct LQElement
{
	LQElement(data dat);

	data _dat;
	LQElement *_next;
};

//----------------------------------------------------

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
class ListQueue: public BasicQueue<data>
{
public:
	ListQueue();
	~ListQueue();
	void enqueue(data dat);
	data dequeue();
	unsigned getLength();

private:
	LQElement<data> *_tail;
	LQElement<data> *_head;
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
	unsigned _size;
	data *_arr;
	unsigned _head;
	unsigned _tail;
	bool _isEmpty;
};

//----------------------------------------------------

template <typename data>
BasicQueue<data>::~BasicQueue()
{}

template <typename data>
LQElement<data>::LQElement(data dat): _dat(dat), _next(NULL)
{}

template <typename data>
ListQueue<data>::ListQueue(): _head(NULL), _tail(NULL)
{}

template <typename data>
ListQueue<data>::~ListQueue()
{
	while(_head != NULL)
		dequeue();
}

template <typename data>
void ListQueue<data>::enqueue(data dat)
{
	if (_head == NULL)
	{
		_head = _tail = new LQElement<data>(dat);
	}
	else
	{
		_tail->_next = new LQElement<data>(dat);
		_tail = _tail->_next;
	}
}

template <typename data>
data ListQueue<data>::dequeue()
{
	data ret;

	if (_head == NULL)
	{
		std::cerr << "lq empty\n";
		exit(1);
	}
	else
	{
		ret = _head->_dat;
		LQElement<data> *tmp = _head;
		_head = _head->_next;
		delete tmp;

		if (_head == NULL)
			_tail = NULL;
	}

	return ret;
}

template <typename data>
unsigned ListQueue<data>::getLength()
{	
	LQElement<data> *p = _head;
	unsigned n = 0;

	while (p != NULL)
	{
		p = p->_next;
		++n;
	}

	return n;
}

//----------------------------------------------------

template <typename data>
ArrayQueue<data>::ArrayQueue(unsigned max_size):
	_isEmpty(true),
	_size(max_size),
	_head(0),
	_tail(0)
{
	_arr = new data[max_size];
}

template <typename data>
ArrayQueue<data>::~ArrayQueue()
{
	delete _arr;
}

template <typename data>
void ArrayQueue<data>::enqueue(data dat)
{
	if (_head == _tail && !_isEmpty)
	{
		std::cerr << "aq full\n";
		exit(1);
	}

	if (_isEmpty)
		_isEmpty = false;

	_arr[_tail] = dat;
	_tail = (_tail + 1) % _size;
}

template <typename data>
data ArrayQueue<data>::dequeue()
{
	if (_isEmpty)
	{
		std::cerr << "aq empty\n";
		exit(1);
	}

	unsigned ret = _head;

	_head = (_head + 1) % _size;

	if (_head == _tail)
		_isEmpty = true;

	return _arr[ret];
}

template <typename data>
unsigned ArrayQueue<data>::getLength()
{	
	unsigned ret = (_tail - _head) % _size;
	
	if (ret == 0 && !_isEmpty)
		return _size;
	
	return ret;
}
