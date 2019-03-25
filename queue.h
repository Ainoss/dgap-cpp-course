#include <iostream>
#pragma once

typedef int data;

class BasicQueue
{
public:

    // Add element to the end
    virtual void enqueue(data &) = 0;

    // Return first element
    virtual data dequeue() = 0;

    // Get total count of elements
    virtual unsigned getLength() = 0;

};

class ListQueue: public BasicQueue
{
public:
    ListQueue();
    void enqueue(data &);
    data dequeue() ;
    unsigned getLength();

private:
    struct Node {
    Node () {
        m_next = NULL;
    }
    Node(const data& t ) {
        m_t = t;
        m_next = NULL;
    }
    data m_t;
    Node* m_next;
};
    Node*m_head;
};

class ArrayQueue: public BasicQueue
{
public:
    ArrayQueue(unsigned max_size = 64);
     void enqueue(data &);
    data dequeue() ;
    unsigned getLength();
private:
    data *ar;
    int fr,re;
};

