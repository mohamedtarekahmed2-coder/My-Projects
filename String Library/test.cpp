#include <iostream>
#include "str.h"
using namespace std;

int main()
{
    clsString String1;
    clsString String2 ("mohamed1111*** MOHAMED");

    String1.set_str(" / / / / ");

    cout << String1.get_str() << ' ' << String2.get_str() << '\n';
    
    cout << String2.count_words() << '\n';
    cout << String1.count_words() << '\n';
    cout << clsString::count_words("hello)") << '\n';
    
    cout << String2.clean();
    return 0;
}