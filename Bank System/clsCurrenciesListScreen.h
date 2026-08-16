#pragma once

#include <iostream>
#include <iomanip>
#include "clsCurrency.h"
#include "clsScreen.h"
using namespace std;

class clsCurrenciesListScreen : protected clsScreen
{
private:
    static void PrintCurrencyRecordLine(clsCurrency Currency)
    {
        cout << "| " << left << setw(30) << Currency.Country();
        cout << "| " << left << setw(8)  << Currency.CurrencyCode();
        cout << "| " << left << setw(45) << Currency.CurrencyName();
        cout << "| " << left << setw(10) << Currency.Rate();
    }

public:
    static void ShowCurrenciesListScreen()
    {
        vector<clsCurrency> vCurrencies = clsCurrency::GetCurrenciesList();

        string Title = "Currency List Screen";
        string SubTitle = '(' + to_string((int)vCurrencies.size()) + ") Currency(s).";
        clsScreen::_DrawScreenHeader(Title, SubTitle);
        cout << "\n__________________________________________________________________________________________________________\n\n";
        cout << "| " << left << setw(30) << "Country";
        cout << "| " << left << setw(8)  << "Code";
        cout << "| " << left << setw(45) << "Name";
        cout << "| " << left << setw(10) << "Rate/(1$)";
        cout << "\n__________________________________________________________________________________________________________\n\n";
        if (vCurrencies.size() == 0)
            cout << "No Data Exist";
        else
        {
            for (clsCurrency &Currency : vCurrencies)
            {
                PrintCurrencyRecordLine(Currency);
                cout << '\n';
            }
        }
        cout << "\n__________________________________________________________________________________________________________\n\n";
    }
};
