
#include <iostream>
#include "queue.h"

using namespace std;

int main()
{
	char c;
	cout << "Type of queue (a - array, l - list): ";
	cin >> c;
	unsigned size = 0;
	
	BasicQueue *queue = NULL;
	if (c == 'a')
	{
		cout << "Max size: ";
		cin >> size;
		queue = new ArrayQueue(size);
	}
	else if (c == 'l')
		queue = new ListQueue;
	else
	{
		cout << "Bad type, exit" << endl;
		return 1;
	}
	
	cout << "Length: " << queue->getLength() << endl;

	cout << "Number of members for enqueue: ";
	cin >> size;
	int i = 0;
	int a = 0;
	for (i = 0; i < size; i++)
	{
		cin >> a;
		queue->enqueue(a);
	}

	cout << "Length: " << queue->getLength() << endl;

	cout << "Number of members for dequeue: ";
	cin >> size;
	for (i = 0; i < size; i++)
	{
		cout << queue->dequeue() << endl;
	}
	
	cout << "Length: " << queue->getLength() << endl;

	delete queue;
	return 0;
}

