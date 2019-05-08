
#include <iostream>
#include <string>
#include "storage.h"

using namespace std;

int main()
{
    int i = 33;

    // With int it works very well, holding actual value:
    Storage<int> st_int(i);
    cout << "Stored int " << st_int.GetVal() << endl;
    cout << "New val: ";
    cin >> i;
    st_int.SetVal(i);
    cout << "Stored int " << st_int.GetVal() << endl;

    // But with usual char* it doesn't work:
    char str[100] = "Hello";
    Storage<char*> st_str(str);
    cout << "Stored str " << st_str.GetVal() << endl;
    str[5] = 'X';
    // Value in storage broken:
    cout << "Stored str " << st_str.GetVal() << endl;
    cout << "New val: ";
    cin >> str;
    st_str.SetVal(str);
    cout << "Changed str " << st_str.GetVal() << endl;
    cout << "New val: ";
    cin >> str;
    st_str.SetVal(str);
    cout << "Changed str " << st_str.GetVal() << endl;

    return 0;
}

