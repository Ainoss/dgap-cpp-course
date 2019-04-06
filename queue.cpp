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
void ArrayQueue::enqueue(data &c)
{	
	int k = this->tale;
	this->dat[k] = c;
	this->tale = (this->tale + 1) % this->lar;
	this->lon++;
}
data ArrayQueue::denqueue()
{
	data x;
	x = dat[(this->hade + 1)%this->lar] ;
	this->hade = (this->hade + 1) % this->lar;
	this->lon--;
	return(x);
}	
unsigned ArrayQueue::getLength()
{
	return(this->lon);
}
void ListQueue::enqueue(data &c)
{	
	this->last->nod = new List;
	this->last->val = c;
	this->last = this->last->nod;
	this->lon++;
}
ListQueue::ListQueue()
{	
		
	this->first = new List;
	this->last = this->first;
	this->lon = 0;
}
data ListQueue::denqueue()
{
	data x;
	List *n;
	n = this->first->nod;
	x = this->first->val;
	delete this->first;
	this->first = n;
	this->lon--;
	return(x);
}
unsigned ListQueue::getLength()
{
	return(this->lon);
}
	
	


