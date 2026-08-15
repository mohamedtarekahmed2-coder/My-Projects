#include <iostream>
#include "clsLoginScreen.h"
#include "clsCurrency.h"
using namespace std;

static void _PrintCurrency(clsCurrency Currency)
{
    cout << "\nCurrency Card:\n";
    cout << "_____________________________\n";
    cout << "\nCountry    : " << Currency.Country();
    cout << "\nCode       : " << Currency.CurrencyCode();
    cout << "\nName       : " << Currency.CurrencyName();
    cout << "\nRate(1$) = : " << Currency.Rate();
    cout << "\n_____________________________\n";
}

int main()
{
    /*
    while(true)
    {
        bool TrailsEnd = clsLoginScreen::ShowLoginScreen();
        if(TrailsEnd) break;
    }
    */

    clsCurrency Currency1 = Currency1.FindByCode("egp");

    if (Currency1.IsEmpty())
        cout << "\nCurrency Is Not Found!\n";
    else
        _PrintCurrency(Currency1);

    clsCurrency Currency2 = Currency2.FindByCountry("EGYPT");

    if (Currency2.IsEmpty())
        cout << "\nCurrency Is Not Found!\n";
    else
        _PrintCurrency(Currency2);

    Currency1.UpdateRate(50);
    cout << "Currency1 after updating Rate:\n";
    _PrintCurrency(Currency1);

    return 0;
}