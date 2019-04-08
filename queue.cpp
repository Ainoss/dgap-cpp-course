#include <iostream>
#include "queue.h"

using namespace std;
ArrayQueue::ArrayQueue(int n)
{
	data * ar = new data[n];
	dat = ar;
	hade = 0;
	tale = 1;
	lar = n;
	lon = 0;
}
ArrayQueue::~ArrayQueue()
{
	delete(dat);
}
void ArrayQueue::enqueue(data &c)
{	
	int k = tale;
	dat[k] = c;
	tale = (tale + 1) % lar;
	lon++;
}
data ArrayQueue::denqueue()
{
	data x;
	x = dat[(hade + 1)%lar] ;
	hade = (hade + 1) % lar;
	lon--;
	return(x);
}	
unsigned ArrayQueue::getLength()
{
	return(lon);
}
void ListQueue::enqueue(data &c)
{	
	last->nod = new List;
	last->val = c;
	last = last->nod;
	lon++;
}
ListQueue::ListQueue()
{		
	first = new List;
	last = first;
	lon = 0;
}
ListQueue::~ListQueue()
{
	while(lon != 0)
	{
		List *l = NULL;
		l = first->nod;
		delete(first);
		first = l;
		lon--;
	}
}
data ListQueue::denqueue()
{
	data x;
	List *n;
	n = first->nod;
	x = first->val;
	delete first;
	first = n;
	lon--;
	return(x);
}
unsigned ListQueue::getLength()
{
	return(lon);
}
	
	


