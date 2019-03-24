
typedef int data;
typedef struct List
{
	data val;
	List *nod;
};
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
	public:
		int hade;
		int tale;
		data * dat;
		int lon;
	ArrayQueue(int n);
  	void  enqueue(data &c);
	data  denqueue();	
	unsigned getLength();	
};
class ListQueue: public BasicQueue
{
	public:
	List *first;
	List *last;
	int lon;
	void  enqueue(data &c);
	ListQueue();
	data denqueue();
	unsigned getLength();
};
