#pragma once

#include <cstring>

using namespace std; // в таком простом случае эта команда в .h-файле никаких проблем не вызовет

template <typename T>
class Storage {
public:
    Storage() = default;
    Storage(const T &val) : m_val(val) {};
    ~Storage() = default;

    void SetVal(const T &val) {m_val = val;}
    T GetVal() const {return m_val;}

private:
    T m_val;
};

template < >
class Storage <char*> {
public:
    Storage() : m_val(nullptr) {}
    Storage(const char* val);
    ~Storage();

    void SetVal(const char* val);
    char* GetVal() const;

private:
    char* m_val;
};

Storage<char*>::Storage(const char* val) :
    m_val([val] () {
        char* m_val_ = new char[strlen(val) + 1];
        strcpy(m_val_, val);
        return m_val_;
    } ()) {};

Storage<char*>::~Storage() {
    delete[] m_val; //проверка m_val != nullptr не нужна, т.к. обработка случая delete для nullptr уже зашита в nullptr и не имеет никакого эффекта
}

void Storage<char*>::SetVal(const char* val) {
    delete[] m_val;
    m_val = new char[strlen(val) + 1];
    strcpy(m_val, val);
}

char* Storage<char*>::GetVal() const {
    if (m_val == nullptr)
        return nullptr; // в случае чего, все необходимые exception будут кинуты при обращении к строке-результату вызова функции
    char* res = new char[strlen(m_val) + 1];
    strcpy(res, m_val);
    return res;
}

// На самом деле, стоит ещё в main отдельно очищать полученную строку, т.к. она создана оператором new. Обходного пути придумать не могу. Поэтому main я немного изменил.
