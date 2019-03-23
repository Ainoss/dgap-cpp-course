
#include "queue.h"
#include <cstdlib>


List* ListQueue::new_l()
{
       return new List;
}

void ListQueue::del_l(List *l)
{
	delete l->Data;
	if (l->next != nullptr)
	{
		del_l(l->next);
		delete l->next;
	}
}

ListQueue::ListQueue()
{
	this->list = new_l();
}

ListQueue::~ListQueue()
{
	del_l(list);
}

void ListQueue::enqueue(data &d)
{
	if (list->Data == nullptr)
	{
		list->Data = new data;
		*(list->Data) = d;
	}
	else
	{
		List* l = new_l();
		l->Data = new data;
		*(l->Data) = d;
		l->next = list;
		list = l;
	}
}

data ListQueue::dequeue()
{
	if (list->Data != nullptr)
	{
		data a = *(list->Data);
		List* l = list;
		list = l->next;
		delete l->Data;
		delete l;
		return a;
	}
	else
		exit(1);
}

unsigned ListQueue::getLength()
{
	if (list->Data == nullptr) return 0;
	List* l = list;
	unsigned i = 1;
	while (l->next != nullptr)
	{
		i++;
		l = l->next;
	}
	return i;
}


ArrayQueue::ArrayQueue(unsigned max_size): array(new data [max_size]), first(0), last(0), max_len(max_size) {}

ArrayQueue::~ArrayQueue()
{
	delete[] array;
}

void ArrayQueue::enqueue(data &d)
{
	array[((first++) - 1) % max_len] = d;
	if (first - last == max_len + 1) last ++;
}

data ArrayQueue::dequeue()
{
	if (last == first) exit (1);
	return array[((last++)-1) % max_len];
}

unsigned ArrayQueue::getLength()
{
	return first - last;
}


