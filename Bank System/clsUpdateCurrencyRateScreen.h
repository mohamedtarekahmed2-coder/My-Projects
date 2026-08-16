#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsCurrency.h"
using namespace std;

class clsUpdateCurrencyRateScreen : protected clsScreen
{
private:
    static float _ReadRate()
    {
        cout << "\nEnter New Rate: ";
        return clsInputValidate::Read<float>();
    }

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

public:
    static void ShowUpdateCurrencyRateScreen()
    {
        system("cls");
        _DrawScreenHeader("Update Currency Screen");

        cout << "\nPlease Enter Currency Code: ";
        string CurrencyCode = clsInputValidate::Read<string>();
        while (!clsCurrency::IsCurrencyExist(CurrencyCode))
        {
            cout << "\nCurrency isn't found, Choose another one: ";
            CurrencyCode = clsInputValidate::Read<string>();
        }
        clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);

        _PrintCurrency(Currency);
        
        cout << "\nAre you sure you want to update the rate of this Currency? [y/n] ";
        char Answer = clsInputValidate::Read<char>();
        if (Answer == 'y' || Answer == 'Y')
        {
            cout << "\nUpdate Currency Rate:";
            cout << "\n_____________________";
            Currency.UpdateRate(_ReadRate());
            cout << "\nCurrency Rate Update Successfully.\n";
            _PrintCurrency(Currency);
        }
    }
};
