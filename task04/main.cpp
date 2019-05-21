#include <iostream>
#include <string>
#include "storage.h"

using namespace std;

int main()
{
	int i = 137;

	Storage<int> st_int(i);
	cout << "Saved integer value: " << st_int.GetVal() << endl;
	cout << "Added new value: ";
	cin >> i;
	st_int.SetVal(i);
	cout << "Stored int " << st_int.GetVal() << endl;

	char str[100] = "Bonjour";
	Storage<char*> st_str(str);
	cout << "Saved string: " << st_str.GetVal() << endl;

	Storage<char*> s;
	try {
		cout << s.GetVal() << endl;
	}
	catch (range_error& er) {
		cerr << er.what() << endl;
	}
	s.SetVal("Hola, MIPT!");
	cout << s.GetVal() << endl;
	s.SetVal("Hola");
	cout << s.GetVal() << endl;
	s.SetVal("Hola, MIPT!");
	cout << s.GetVal() << endl;
	system("pause");
	return 0;
}