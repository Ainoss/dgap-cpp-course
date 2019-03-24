
#include <iostream>
#include "queue.h"

using std::cout, std::cin, std::endl, std::string;

int main()
{
    unsigned n;
    cout << "Number of elements in a queue: ";
    cin >> n;

    char c;
    cout << "Type of queue (a - array, l - list): ";
    cin >> c;
    
    BasicQueue *queue = nullptr;
    if (c == 'a')
        queue = new ArrayQueue (n);
    else if (c == 'l')
        queue = new ListQueue;
    else {
        cout << "Bad type, exit" << endl;
        return 1;
    }



    int i=0;
    try {
        for (i; i<n; i++)
        {
            queue->enqueue(i);
            cout<< queue->dequeue()<<endl;
        }
    }
    catch (char const* error){
            cout<< error<< endl;
            delete queue;
            exit (1);}

    /*
     * Put here your tests: en/dequeue large number of elements
     */
    delete queue;
    return 0;
}

