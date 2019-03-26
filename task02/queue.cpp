#include "queue.h"
#include <iostream>
#include <stdlib.h>

ListQueue :: ListQueue (){
    m_head = NULL;
}

void ListQueue :: enqueue (data &a){
    if (Node* node = new Node(a)){
        node->m_next = m_head;
        m_head = node;
    }
}

data ListQueue :: dequeue () {
    if (m_head) {
        if(this->getLength()==1)
        return m_head->m_t;
        Node* newHead = m_head;
        int i = 0;
        while(i<(this->getLength()-2)){
            newHead = newHead->m_next;
            i++;
        }
        Node*p=newHead;
        Node *p1 = newHead->m_next;
        p->m_next = NULL;
        newHead = p1;
        data d = newHead->m_t;
        delete newHead;
        return(d);
    } else std:: cout<<"is empty" << std::endl;
}

unsigned ListQueue:: getLength() {
    int i = 0;
    Node* p = m_head;
    while (p != NULL) {
        i++;
        p = p->m_next;
    }
    return(i);
}

ArrayQueue::ArrayQueue(unsigned max_size ) {
    fr = 1;
    re = 0;
    ar = (data*)malloc (max_size*sizeof(data));
}

void ArrayQueue :: enqueue(data &a) {
    if(re < 63) {
        re++;
        ar[re] = a;
    }
    else
        std::cout<<"Stack overflow"<<std::endl;
}

data ArrayQueue :: dequeue() {
    if (re<fr)  {
        std::cout<<"Stack is empty"<<std::endl;
        return 0;
    }
    else {
        data x = ar[fr];
        fr++;
        return (x);
    }
}

unsigned ArrayQueue:: getLength() {
    return (re-fr+1);
}
