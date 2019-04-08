#include <iostream>
#include "queue.h"
using namespace std;

int main()
{
	int a = 0;
	int x = 7, y = 8;
	BasicQueue<int>* queue = NULL;

	try {

		if(a == 0) queue = new ArrayQueue<int>;
		else queue = new ListQueue<int>;
		queue->enqueue(x);
		queue->enqueue(y);
		cout << queue->getLength() << endl;
		cout << queue->dequeue() << endl;
		cout << queue->getLength() << endl;
		cout << queue->dequeue() << endl;
		cout << queue->getLength() << endl;
		queue->enqueue(x);
		queue->enqueue(y);
		cout << queue->dequeue() << endl;
		cout << queue->dequeue() << endl;
		queue->enqueue(x);
		queue->enqueue(y);
		cout << queue->dequeue() << endl;
		cout << queue->dequeue() << endl;
		delete queue;
	}
	catch (exception &e)
	{
		cerr << "Caught: " << e.what() << endl;
		cerr << "Type: " << typeid(e).name() << endl;
	};

	return 0;
}

