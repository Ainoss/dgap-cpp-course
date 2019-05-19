#pragma once
#include <cstring>
#include <algorithm>

template <typename T>
class Storage
{
public:
    Storage() = default;

    Storage(const T &val):
        m_val(val)
    {}

    ~Storage() {}

    void SetVal(const T &val)
    {
        m_val = val;
    }

    T GetVal()
    {
        return m_val;
    }
private:
    T m_val;
};


template <>
class Storage<char*>
{
public:
    Storage(const char* val = NULL)
    {
        m_val = new char[sizeof(char)*strlen(val) + 1];
        std::copy(val, val + strlen(val) + 1, m_val);
        //for (int i = 0; i <= strlen(val); i++)
            //m_val[i] = val[i];
    }

    ~Storage()
    {
        delete [] m_val;
    }

    void SetVal(const char* val)
    {
        delete [] m_val;
        m_val = new char[sizeof(char)*strlen(val) + 1];
        std::copy(val, val + strlen(val) + 1, m_val);
        //for (int i = 0; i <= strlen(val); i++)
            //m_val[i] = val[i];
    }
    char* GetVal()
    {
        return m_val;
    }

private:
    char* m_val;
};