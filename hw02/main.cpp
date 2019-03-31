#include <iostream>
#include "queue.h"

typedef int T;

int main()
{
	char c;
	T a;
	unsigned s;
	
    std::cout << "Type of queue (a - array, l - list): ";
    std::cin >> c;
    
    BasicQueue<T> *queue = NULL;
    if (c == 'a')
	{
		std::cout << "size: ";
		std::cin >> s;
        queue = new ArrayQueue<T>(s);
		std::cout << "\n";
	}
    else if (c == 'l')
	{
        queue = new ListQueue<T>;
		std::cout << "\n";
	}
    else
	{
        std::cout << "Bad type, exit" << "\n";
        return 1;
    }
	
	std::cout << "e x - enqueue x, d - dequeue, l - length, q - quit\n\n";
	
    while (true)
	{
		std::cin >> c;
		
		if (c == 'e')
		{
			std::cin >> a;
			queue->enqueue(a);
			std::cout << "enqueued " << a << std::endl;
			std::cout << "length: " << queue->getLength() << "\n\n";
		}
		else if (c == 'd')
		{
			T out;
			out = queue->dequeue();
			std::cout << "dequeued " << out << std::endl;
			std::cout << "length: " << queue->getLength() << "\n\n";
		}
		else if (c == 'l')
		{
			std::cout << "length: " << queue->getLength() << "\n\n";
		}
		else if (c == 'q')
		{
			break;
		}
		else
		{
			std::cout << "no such option, exiting...\n";
			return 1;
		}
	}

    delete queue;
	
    return 0;
}
