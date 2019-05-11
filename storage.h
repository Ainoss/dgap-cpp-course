#include<vector>
using namespace std;
template <typename T>
class Storage
{
public:
	~Storage() = default;
	Storage() = default;
	Storage(const T& val);
	void SetVal(const T& val);
	T GetVal();
private:
	T m_val;
};
template <>
class Storage <char*>
{
private:
	vector <char> type;
public:
	Storage() = default;
	~Storage();
	Storage(char* val);

	void SetVal(char* s);
	char* GetVal();
};
template <typename T>
Storage<T>::Storage(const T& val)
{
	m_val = val;
}

template<typename T>
void Storage<T>::SetVal(const T& val)
{
	m_val = val;
}

template<typename T>
T Storage<T>::GetVal()
{
	return(m_val);
}
Storage<char*>::Storage(char* val)
{
	int c = 0;
	while (val[c] != '\0')
	{
		type.push_back(val[c]);
		c++;
	}
	type.push_back('\0');
}

void Storage<char*>::SetVal(char* s)
{
	int c = 0;
	while (s[c] != '\0')
	{
		type.push_back(s[c]);
		c++;
	}
	type.push_back('\0');
}
Storage<char*>::~Storage()
{
	type.clear();
}
char* Storage<char*>::GetVal()
{
	int l = type.size();
	char* s = new char[l];
	for (int c = 0; c < l; c++)
		s[c] = type[c];
	return(s);
}
