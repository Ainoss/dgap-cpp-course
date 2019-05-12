#pragma once
#include <cstring>

template <typename T>
class Storage
{
public:
	Storage() = default;
	Storage(const T &val) {
		m_val = val;
	}

	~Storage() {
		delete m_val
	}

	void SetVal(const T &val) {
		m_val = val;
	}

	T GetVal() {
		return m_val;
	}

private:
	T m_val;
};

template<>
class Storage<char*>
{
public:	
		Storage() = default;
		Storage(const char* val) {
			char* m_val = new char[strlen(val) + 1];
			std::strcpy(m_val, val);
		}
			
		~Storage() {
			delete m_val;
		}

		void SetVal(const char* val) {
			char* m_val = new char[strlen(val)+1];
			std::strcpy(m_val, val);
			delete m_val;
		}	

		char* GetVal() {
			return m_val;
		}

private:
	char* m_val;

};
