#include <iostream>
#include "queue.h"


using namespace std;
	ArrayQueue::ArrayQueue(int n)
	{
		data * ar = new data[n];
		this->dat = ar;
		
	    
		hade = 0;
		tale = 1;
		this->lar = n;
		lon = 0;

    }
  	void ArrayQueue::enqueue(data &c)
	{	
		int k = this->tale;
		dat[k] = c;
		this->tale = (this->tale + 1) % this->lar;
		this->lon++;
	
	}
	data ArrayQueue::denqueue()
	{
			data x;
		x = dat[this->hade + 1] ;
		
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
		x = this->first->val;
		this->first = this->first->nod;
		this->lon--;
		return(x);
	}
	unsigned ListQueue::getLength()
	{
		return(this->lon);
	}
	
	


