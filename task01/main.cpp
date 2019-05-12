
#include <iostream>
#include "complex.h"

int main()
{
    C a, b(2.0), c(1.0, 1.0);
    a = a * C(2.0);
    a += c;
    c = a + 2 * b;

    std::cout << a << ", " << c << std::endl;

    return 0;
}
