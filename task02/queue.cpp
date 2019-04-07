#include <iostream>
#include "queue.h"

typedef int T;

int main()
{
	char c;
	T a;
	unsigned s;
	std::cout << " a - array, l - list " << std::endl;
	std::cin >> c;
	BasicQueue<T> *queue = NULL;
	if (c == 'a')
	{
		std::cout << " size: " << std::endl; 
		std::cin >> s; 
		queue = new ArrayQueue<T>(s);	
	}
	else if (c == 'l')
	{
		queue = new ListQueue<T>;
	}
	else 
	{
		std::cout << " It is wrong type " << std::endl;
		return 1;
	}

	std::cout << " e - enqueue, d - dequeue, g - getLength, q - quit " << std::endl;

	while (true)
	{
		std::cin >> c;
		if (c == 'e')
		{
			std::cin >> a;
			queue->enqueue(a);
			std::cout << a << std::endl;
			std::cout << queue->getLength() << std::endl;
		}
		else if (c == 'd')
		{
			T out;
			out = queue->dequeue();
			std::cout << out << std::endl;
			std::cout << queue->getLength() << std::endl;
		}
		else if (c == 'g')
		{
			std::cout << queue->getLength() << std::endl;
		}
		else if (c == 'q')
		{
			break;
		}
		else 
		{
			std::cout << "It is wrong type " << std::endl;
			return 1;
		}
	}

		delete queue;

		return 0;
}
