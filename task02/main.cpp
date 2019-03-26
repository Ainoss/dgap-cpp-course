
#include <iostream>
#include "queue.h"
#include "queue.cpp"

#define N  50


int main()
{
    char c;
    std::cout << "Type of queue (a - array, l - list): ";
    std::cin >> c;

    BasicQueue *queue = NULL;
    if (c == 'a')
        queue = new ArrayQueue;
    else if (c == 'l')
        queue = new ListQueue;
    else {
        std::cout << "Bad type, exit" << std::endl;
        return 1;
    }
    int j;
    data&j1=j;
    for (j= 0 ; j <N; j++) {
        std::cout<<j<<std::endl;

        queue->enqueue(j);
    }
    std::cout<<" "<<std::endl;
    int len = queue->getLength();
    for (j= 0 ; j <len; j++) {
        std::cout<<queue->dequeue()<<std::endl;
    }
    delete queue;
    return 0;
}

