#include <cstring>

template <typename T>
class Storage
{
public:
	Storage() = default;
	Storage(const T &val): m_val(val) {};
	~Storage(){}

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
class Storage<char *>
{
public:
	Storage() = default;
	Storage(const char* val)
	{
		m_val = (char*)malloc(sizeof(val));
		strcpy(m_val, val);
	}
	~Storage()
	{
		free(m_val);
	}

	void SetVal(const char* val)
	{
		realloc(m_val, sizeof(val));
		strcpy(m_val, val);
	}
	char* GetVal()
	{
		return m_val;
	}
private:
	char* m_val;
};
