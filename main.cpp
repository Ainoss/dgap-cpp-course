#include <iostream>
#include "queue.h"
using namespace std;

 int main()
 {
    char c;
    std::cout << "Type of queue (a - array, l - list): ";
    std::cin >> c;
	BasicQueue *queue = NULL;
    if (c == 'a')
        queue = new ArrayQueue(20);
    else if (c == 'l')
    	queue = new ListQueue;
    else {
        std::cout << "Bad type, exit" << std::endl;
        return 1;
    }

	
    for (c = 0;c < 10;c++)
    {	
	cin >> d;
	queue->enqueue(d);
	cout << queue->getLength() << endl;
    }
    for (c = 0;c < 10;c++)
    {
	cout << queue->denqueue()  << " ";
	cout << queue->getLength() << endl;
    }
    delete queue;
    return 0;
}

	

