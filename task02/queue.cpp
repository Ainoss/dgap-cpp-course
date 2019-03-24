//
// Created by jacknondaniels on 21.03.19.
//
#include <iostream>
#include "queue.h"

template <typename T>  class Note
{
public:
    void setnext (Note *ptr) {next = ptr;}
    Note *getnext () {return next;}
    T &getdata () {return body;}
    Note (T a = 0):
            body (a),
            next (nullptr)
    {};
private:
    T body;
    Note * next;
};

template <typename T>  class ListQueue: public BasicQueue <T>
{
public:
    ListQueue ():
            head (nullptr),
            size (0)
    {};

    ~ListQueue() final
    {if (head) {
            Note<T> *current;
            while (head->getnext())
            {
                current = head;
                head = current->getnext();
                delete current;
            };
            delete head;
        }
    };

    void enqueue (T&a) override  {
        if (head)
        {
            Note<T> *current = head;
            while (current->getnext())
                current = current->getnext();
            current->setnext(new Note<T> (a));
            if (!current->getnext())
                throw ("no space available");
        }
        else if (!(head = new Note<T> (a) ))
            throw ("no space available");
        size++;
    };

    T dequeue () override  {
        if (getLength() <= 0)
            throw ("no elements in queue");
        else {
            T a = head->getdata();
            Note<T> *ptr = head;
            head = head->getnext();
            delete ptr;
            size--;
            return a;
        }
    };

    unsigned getLength() override {return size;}

private:
    Note <T> *head;
    unsigned size;
};

template <typename T>  class ArrayQueue: public BasicQueue <T>
{
public:
    ArrayQueue(unsigned max_size = 64):
        m_size(max_size),
        current_number(0),
        size (0)
    {
        if (!(array = new T [m_size]))
            throw ("no space available");
    };

    ~ArrayQueue() final  {
        delete [] array;
        current_number = 0;
        size = 0;
    };

    void enqueue (T& new_one) override  {
        if (size >= m_size)
            throw ("it's too much, huh");
        else{
            array[current_number % m_size] = new_one;
            current_number++;
            size++;
        }
    };

    T dequeue () override{
        if (getLength() <= 0)
            throw ("no elements in queue");
        else
            return array[( current_number - (size--) ) % m_size];
    };

    unsigned getLength () override {return size;};

private:
    T *array;
    unsigned m_size;
    unsigned current_number;
    unsigned size;
};