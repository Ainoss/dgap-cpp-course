
#pragma once

template <typename T>
        class BasicQueue
{
public:
    virtual void enqueue(T &) = 0;
    virtual T dequeue() = 0;
    virtual unsigned getLength() = 0;
    virtual ~BasicQueue() {};
};

template <typename T>  class Note;
template <typename T>  class ListQueue;
template <typename T>  class ArrayQueue;

