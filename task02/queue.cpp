
#include "queue.h"
#include <cstdlib>


void ListQueue::del_l(List *l)
{
	if (l != nullptr)
	{
		if (l->next != nullptr)
		{
			del_l(l->next);
			delete l->next;
		}
	}
}

ListQueue::ListQueue()
{
	tail = new List;
	list = nullptr;
}

ListQueue::~ListQueue()
{
	del_l(list);
}

void ListQueue::enqueue(data &d)
{
	if (tail == nullptr)
	{
		tail = new List;
		tail->Data = d;
		list = tail;
	}
	else if (list == nullptr)
	{
		list = tail;
	}
	else
	{
		tail->next = new List;
		tail = tail->next;
	}
	tail->Data = d;
}

data ListQueue::dequeue()
{
	if (list == nullptr)
		exit(1);
	data a = list->Data;
	if (list != tail)
	{
		List* l = list;
		list = list->next;
		delete l;
	}
	else
	{
		delete list;
		list = nullptr;
	}
	return a;
}

unsigned ListQueue::getLength()
{
	if (list == nullptr)
	       return 0;
	List* l = list;
	unsigned i = 1;
	while (l != tail)
	{
		i++;
		l = l->next;
	}
	return i;
}


ArrayQueue::ArrayQueue(unsigned max_size):
	array(new data [max_size]),
	first(0),
	last(0),
	max_len(max_size)
{
}

ArrayQueue::~ArrayQueue()
{
	delete[] array;
}

void ArrayQueue::enqueue(data &d)
{
	if ((first % max_len == last % max_len) && (first != last))
		exit(1);
	array[first % max_len] = d;
	first++;
}

data ArrayQueue::dequeue()
{
	if (last == first)
		exit (1);
	last++;
	return array[(last - 1) % max_len];
}

unsigned ArrayQueue::getLength()
{
	return first - last;
}


