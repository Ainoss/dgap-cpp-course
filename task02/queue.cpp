//
// Created by jacknondaniels on 21.03.19.
//

#include <iostream>
#include "queue.h"

Note::Note (data a):
body (a),
next (nullptr)
{}


ListQueue::ListQueue():
 head (nullptr),
 size (0)
{}

ListQueue::~ListQueue() {if (head) {
        Note *current;
        while (head->getnext())
        {
            current = head;
            head = current->getnext();
            delete current;
        };
        delete head;
        std::cout << "Deleting the notes in list" << std::endl;
    }
}

void ListQueue::enqueue(data & a) {
    if (head)
    {
        Note *current = head;
        while (current->getnext())
            current = current->getnext();
        current->setnext(new Note (a));
    }
    else if (!(head = new Note (a) ))
        throw ("no space available");
    size++;
}

data ListQueue::dequeue() {
    if (getLength() <= 0)
        throw ("i'm afraid i got nothing to show");
    else {
        data a = head->getdata();
        Note *ptr = head;
        head = head->getnext();
        delete ptr;
        size--;
        return a;
    }
}

ArrayQueue::ArrayQueue(unsigned int max_size):
 m_size(max_size),
 current_number(0),
 size (0)
{
    array = new data [m_size];
    std::cout<< "i'm built!!!"<< std::endl;
}

ArrayQueue::~ArrayQueue() {
    delete [] array;
    current_number = 0;
    size = 0;
    std::cout<< "let me fade away"<< std::endl;
}

data ArrayQueue::dequeue() {
    if (getLength() <= 0)
        throw ("i'm afraid i got nothing to show");
    else
        return array[( current_number - (size--) ) % m_size];}

void ArrayQueue::enqueue(data &new_one) {
    if (size >= m_size)
            throw ("it's too much, huh");
    else{
        array[current_number % m_size] = new_one;
        current_number++;
        size++;
    }

}