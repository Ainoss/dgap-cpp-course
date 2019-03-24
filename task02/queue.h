
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
    virtual ~BasicQueue() {};
};

class Note
{
public:
    void setnext (Note *ptr) {next = ptr;}
    Note *getnext () {return next;}
    data &getdata () {return body;}
    Note (data a = 0);

private:
    data body;
    Note * next;
};

class ListQueue: public BasicQueue
{
public:
    ListQueue();
    ~ListQueue() final;

    void enqueue (data&) override;
    data dequeue () override;
    unsigned getLength() override {return size;}

private:
    Note *head;
    unsigned size;
    /*
     * Fully implement class:
     * - declarations here
     * - definitions in queue.cpp
     * Could have infinite size
     */
};

class ArrayQueue: public BasicQueue
{
public:
    ArrayQueue(unsigned max_size = 64);
    ~ArrayQueue() final;

    void enqueue (data&) override;
    data dequeue () override;
    unsigned getLength () override {return size;};

private:
    data *array;
    unsigned m_size;
    unsigned current_number;
    unsigned size;
    /*
     * Fully implement class:
     * - declarations here
     * - definitions in queue.cpp
     * Only finite size implementation is required
     */
};

