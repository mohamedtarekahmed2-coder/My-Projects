#include <iostream>
#include "clsLoginScreen.h"
using namespace std;

int main()
{
    while (true)
    {
        bool TrailsEnd = clsLoginScreen::ShowLoginScreen();
        if (TrailsEnd) break;
    }
    return 0;
}