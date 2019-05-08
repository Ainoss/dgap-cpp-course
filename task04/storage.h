#pragma once
#include <iostream>
#include <cstring>


template <typename T>
class Storage
{
public:
    Storage() = default;
    Storage(const T &val):
    m_val(val)
    {};
    ~Storage() = default;

    void SetVal(const T &val){
        m_val = val;
    };
    T GetVal(){
        return m_val;
    };
private:
    T m_val;
};

template <> class Storage<char*> {

private:
    char *m_val;
    unsigned m_size;
public:
    Storage (const char* val)
    {
        m_size = strlen(val);
        m_val = new char [m_size+1];
        strcpy(m_val, val);
    };
    ~Storage(){
        delete[] m_val;
    };
    void SetVal (const char* val){
        unsigned n = strlen(val);
        if (n > m_size) {
            m_size = n;
            delete[] m_val;
            m_val = new char[n+1];
        }
       strcpy(m_val, val);
    };
    char* GetVal(){
        return m_val;
    };
};
