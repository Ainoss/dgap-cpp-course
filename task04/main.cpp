#include "storage.h"

#include <iostream>
#include <string>

using namespace std;

int main() {
    int i = 33;

    // With int it works very well, holding actual value:
    Storage<int> st_int(i);
    cout << "Stored int " << st_int.GetVal() << endl;
    cout << "New val: ";
    cin >> i;
    st_int.SetVal(i);
    cout << "Stored int " << st_int.GetVal() << endl;

    // It works with usual char* as well:
    char str[100] = "Hello";
    Storage<char*> st_str(str);
    
    char* output = st_str.GetVal();
    cout << "Stored str " << output << endl;
    delete[] output; // imporant!

    str[1] = 'X';
    // Value in storage is still OK:
    output = st_str.GetVal();
    cout << "Stored str " << output << endl;
    delete[] output; // imporant!

    return 0;
}
