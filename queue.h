
typedef int data;
class BasicQueue	
{
	public:
		virtual void enqueue(data &c) = 0;
		virtual data  denqueue() = 0;
		virtual unsigned getLength() = 0;	
};
class ArrayQueue: public BasicQueue
{
	private:
		int lar;
		int hade;
		int tale;
		data * dat;
		int lon;
	public:	
	ArrayQueue(int n);
	~ArrayQueue();
  	void  enqueue(data &c);
	data  denqueue();	
	unsigned getLength();	
};

class ListQueue: public BasicQueue
{
	private:
	typedef struct List
	{
		data val;
		List *nod;
	};
	List *first;
	List *last;
	int lon;
	public:
	void  enqueue(data &c);
	ListQueue();
	~ListQueue();
	data denqueue();
	unsigned getLength();
};
