#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsCurrency.h"
using namespace std;

class clsFindCurrencyScreen : protected clsScreen
{
private:
    enum enFindCurrencyOptions
    {
        eCode = 1,
        eCountry
    };

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
    
    static void _ShowResults(clsCurrency Currency)
    {
        if (Currency.IsEmpty())
        {
            cout << "\nCurrency was not Found.\n";
        }
        else
        {
            _PrintCurrency(Currency);
        }
    }

    static int _ReadFindCurrencyOption()
    {
        cout << "\nFind By: Code [1] or Country [2]? ";
        return clsInputValidate::ReadNumberBetween<int>(0, 3, "Choose Number Between 1 and 2 ");
    }

    static void _FindByCode()
    {
        cout << "\nPlease Enter Currency Code: ";
        string CurrencyCode = clsInputValidate::Read<string>();
        _ShowResults(clsCurrency::FindByCode(CurrencyCode));
    }

    static void _FindByCountry()
    {
        cout << "\nPlease Enter Country Name: ";
        string Country = clsInputValidate::Read<string>();
        _ShowResults(clsCurrency::FindByCountry(Country));
    }

public:
    static void ShowFindCurrencyScreen()
    {
        system("cls");
        _DrawScreenHeader("Find Currency Screen");

        enFindCurrencyOptions Answer = (enFindCurrencyOptions)_ReadFindCurrencyOption();
        switch (Answer)
        {
        case enFindCurrencyOptions::eCode:
            _FindByCode();
            break;
        case enFindCurrencyOptions::eCountry:
            _FindByCountry();
            break;
        }
    }
};
