#include <iostream>
#include "queue.h"
using namespace std;

int main()
{
	/*
    char c;
    std::cout << "Type of queue (a - array, l - list): ";
    std::cin >> c;
    */
    //BasicQueue<int> * queue = NULL;
	/*
    if (c == 'a')
        queue = new ArrayQueue<int>;
    else if (c == 'l')
        queue = new ListQueue<int>;
    else {
        std::cout << "Bad type, exit" << std::endl;
        return 1;
    }
	*/
	int x = 7, y = 8;
	BasicQueue<int> * queue = NULL;

	/*
	ListQueue<int> * queue_l = new ListQueue<int>;
	queue_l->enqueue(x);
	queue_l->enqueue(y);
	queue = queue_l;
	cout << queue_l->getLength() << endl;
	cout << queue_l->dequeue() << endl;
	cout << queue_l->getLength() << endl;
	cout << queue_l->dequeue() << endl;
	cout << queue_l->getLength() << endl;
	*/
	try {
		ArrayQueue<int> * queue_a = new ArrayQueue<int>;
		queue_a->enqueue(x);
		queue_a->enqueue(y);
		queue = queue_a;
		cout << queue_a->getLength() << endl;
		cout << queue_a->dequeue() << endl;
		cout << queue_a->getLength() << endl;
		cout << queue_a->dequeue() << endl;
		cout << queue_a->getLength() << endl;
		delete queue_a;
	}
	catch (exception &e)
	{
		cerr << "Caught: " << e.what() << endl;
		cerr << "Type: " << typeid(e).name() << endl;
	};

	//delete queue_l;
	return 0;
}

