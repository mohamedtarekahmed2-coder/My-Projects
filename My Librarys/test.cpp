#include <iostream>
#include "clsDate.h"
using namespace std;

int main() 
{
    clsDate ob1;
    ob1.Print();

    // clsDate ob2("2/2/2002");
    // ob2.print();

    // clsDate ob3(3, 3, 2003);
    // ob3.print();

    // clsDate ob4(273, 2022);
    // ob4.print();

    // ob1.print_month_calendar();

    ob1.PrintYearCalendar();
    return 0;
}