
#include <iostream>
#include "queue.cpp"
#include "queue.h"

using std::cout, std::cin, std::endl, std::string;

int main()
{
    typedef string data;
    char c;
    cout << "Type of queue (a - array, l - list): ";
    cin >> c;
    
    BasicQueue <data>  *queue = nullptr;
    try {
        if (c == 'a') {
            cout << "Size of array: ";
            unsigned n;
            cin >> n;
            queue = new ArrayQueue <data> (n);
        }
        else if (c == 'l')
            queue = new ListQueue<data>;
        else {
            cout << "Bad type, exit" << endl;
            return 1;
        }
    }
    catch (char const * error){
        cout<<error<<endl;
        exit (1);
    };


    data d;
    cout << "Action (i - insert, t - take from queue, l - length of a queue, 0 - exit):"<< endl;
    cin>>c;
    try {
        while (c)
        {
            if (c == 'i'){
                cin>>d;
                queue->enqueue(d);
            }
            else if (c == 't')
                cout<<queue->dequeue()<<endl;
            else if (c == 'l')
                cout<<queue->getLength()<<endl;
            else if (c == '0')
                break;
            else
                cout<< "Bad type, try again"<<endl;
            cin>>c;
        }
    }
    catch (char const* error){
            cout<< error<< endl;
            delete queue;
            exit (1);}

    delete queue;
    return 0;
}

