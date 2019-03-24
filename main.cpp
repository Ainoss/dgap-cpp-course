#include "queue.h"
#include <iostream>
using namespace std;
int main()
{
	int c, b;
	data a[12], d;
	ArrayQueue q(20);
	cout << "press 1 if you want ArrayQueue, press 2 if you want ListQueue";
	cin >> b;
	if (b == 2)
		ListQueue q;
	for (c = 0;c < 10;c++)
	{
		cin >> d;
		q.enqueue(d);
	
	}
	for (c = 0;c < 10;c++)
	{
		cout << q.denqueue() << " ";
	}
}
