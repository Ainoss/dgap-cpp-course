#pragma once
#include <string.h>
#pragma warning (disable : 4996)

template <typename T>
class Storage
{
public:
	Storage() = default;
	Storage(const T& val) : m_val(val) {};
	~Storage() = default;

	void SetVal(const T& val) {
		m_val = val;
	};
	T GetVal() {
		return m_val;
	};
private:
	T m_val;
};

template <>
class Storage<char*>
{
public:
	Storage() = default;
	Storage(const char* val) {
		m_val = new char[strlen(val) + 1];
		strcpy(m_val, val);
	};
	~Storage() {
		delete[] m_val;
	};

	void SetVal(const char* val) {
		delete[] m_val;
		m_val = new char[strlen(val) + 1];
		strcpy(m_val, val);
	};
	char* GetVal() {
		return m_val;
	};
private:
	char* m_val;
};