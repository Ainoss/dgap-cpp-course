
#pragma once
#include <iostream>
#include <stdexcept>

template <typename T>
        class BasicQueue
{
public:
    virtual void enqueue(T &) = 0;
    virtual T dequeue() = 0;
    virtual unsigned getLength() = 0;
    virtual ~BasicQueue() {};
};

template <typename T>
        class ListQueue: public BasicQueue <T> {
public:
    ListQueue() :
            head(nullptr),
            size(0),
            tail(nullptr) {};

    ~ListQueue() final {
        if (head) {
            Note *current;
            while (head->getnext()) {
                current = head;
                head = current->getnext();
                delete current;
            };
            delete head;
        }
    };

    void enqueue(T &a) override {
        if (tail) {
            tail->setnext(new Note(a));
            tail = tail->getnext();
        } else {
            head = new Note(a);
            tail = head;
        }
        size++;
    };

    T dequeue() override {
        if (getLength() <= 0)
            throw (std::runtime_error("no elements in queue"));
        else {
            T a = head->getdata();
            Note *ptr = head;
            head = head->getnext();
            delete ptr;
            size--;
            return a;
        }
    };

    unsigned getLength() override { return size; }

private:
    class Note {
    public:
        void setnext(Note *ptr) { next = ptr; }

        Note *getnext() { return next; }

        T &getdata() { return body; }

        explicit Note(T a = 0) :
                body(a),
                next(nullptr) {};
    private:
        T body;
        Note *next;
    };

    Note *head;
    Note *tail;
    unsigned size;

};



template <typename T>
        class ArrayQueue: public BasicQueue <T> {


public:
    explicit ArrayQueue (unsigned given_size = 64):
        max_size(given_size),
        current_number(0),
        size (0),
        array (new T [given_size]) {};

    ~ArrayQueue() final  {
        delete [] array;
        current_number = 0;
        size = 0;
    };

    void enqueue (T& new_one) override  {
        if (size >= max_size)
            throw (std::runtime_error("it's too much, huh"));
        else{
            array[current_number % max_size] = new_one;
            current_number++;
            size++;
        }
    };

    T dequeue () override{
        if (getLength() <= 0)
            throw (std::runtime_error("no elements in queue"));
        else
            return array[( current_number - (size--) ) % max_size];
        };

    unsigned getLength () override {return size;}


private:
        T *array;
        const unsigned max_size;
        unsigned current_number;
        unsigned size;
};

