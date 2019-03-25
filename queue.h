#pragma once
#include <stdexcept>
using namespace std;

template <typename T1>
class BasicQueue
{
public:

    // Add element to the end
    virtual void enqueue(T1 &) = 0;

    // Return first element
    virtual T1 dequeue() = 0;

    // Get total count of elements
    virtual size_t getLength() = 0;

};



template <typename T1>
class ListQueue: public BasicQueue<T1>
{
private:
	template <typename T1>
	class node
	{
	public:
		node(T1 x) : data(x), prev(nullptr) {};

		T1 data;
		node * prev;
	};

	node<T1> * head, *tail;
	size_t size;

public:
	ListQueue() : head(nullptr), tail(nullptr), size(0) {};
	ListQueue(node<T1> * x) : head(x), tail(x), size(1) {};
	ListQueue(ListQueue<T1> & l) : head(l.head), tail(l.tail), size(l.size) {};

	virtual void enqueue(T1 & x);
	virtual T1 dequeue();
	virtual size_t getLength();

    /*
     * Fully implement class:
     * - declarations here
     * - definitions in queue.cpp
     * Could have infinite size
     */
};

template<typename T1>
inline void ListQueue<T1>::enqueue(T1 & x)
{
	if (size == 0) {
		head = tail = new node<T1>(x);
	}
	else {
		head->prev = new node<T1>(x);
		head = head->prev;
	}
	size++;
}


template<typename T1>
inline T1 ListQueue<T1>::dequeue()
{
	T1 buf = tail->data;
	node<T1> * end = tail;
	tail = tail->prev;
	size--;
	delete end;
	return buf;
}


template<typename T1>
inline size_t ListQueue<T1>::getLength()
{
	return size;
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



template <typename T1>
class ArrayQueue: public BasicQueue<T1>
{
public:
	ArrayQueue(unsigned capacity = 1) : head(0), tail(0), size(0), _capacity(capacity)
	{
		_array = new T1[capacity];
	}
	ArrayQueue(ArrayQueue & a) : head(a.head), tail(a.tail), size(a.size), _array(a._array), _capacity(a._capacity) {}
	~ArrayQueue()
	{
		delete[] _array;
	}

	virtual void enqueue(T1 & x);
	virtual T1 dequeue();
	virtual size_t getLength();
private:
	T1 * _array;
	size_t head, tail, size, _capacity;

    /*
     * Fully implement class:
     * - declarations here
     * - definitions in queue.cpp
     * Only finite size implementation is required
     */
};



template<typename T1>
inline void ArrayQueue<T1>::enqueue(T1 & x)
{
	_array[size] = x;
	tail = size;
	size = (size + 1) % _capacity;
	if (size == head) throw logic_error("Queue overflow");

}


template<typename T1>
inline T1 ArrayQueue<T1>::dequeue()
{
	if(size == 0) throw logic_error("Queue is empty");
	size--;
	return _array[head++];
}


template<typename T1>
inline size_t ArrayQueue<T1>::getLength()
{
	return size;
}
