#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsString.h"
#include "clsCurrency.h"
using namespace std;

class clsCurrencyCalculatorScreen : protected clsScreen
{
private:
    static float _ReadAmount()
    {
        cout << "\nEnter Amount to Exchange: ";
        return clsInputValidate::Read<float>();
    }

    static void _PrintCurrencyCard(clsCurrency Currency, string Title)
    {
        cout << '\n' << Title << '\n';
        cout << "_____________________________\n";
        cout << "\nCountry    : " << Currency.Country();
        cout << "\nCode       : " << Currency.CurrencyCode();
        cout << "\nName       : " << Currency.CurrencyName();
        cout << "\nRate(1$) = : " << Currency.Rate();
        cout << "\n_____________________________\n";
    }

    static void _PrintCalculationsResults(float Amount, clsCurrency CurrencyFrom, clsCurrency CurrencyTo)
    {
        _PrintCurrencyCard(CurrencyFrom, "Convert From:");
        _PrintCurrencyCard(CurrencyTo, "Convert To:");
        float Result = (Amount * CurrencyTo.Rate()) / CurrencyFrom.Rate();
        cout << Amount << ' ' << CurrencyFrom.CurrencyCode() << " = " << Result << ' ' << CurrencyTo.CurrencyCode() << '\n';
    }

    static string _ReadCurrencyCode()
    {
        string CurrencyCode = clsInputValidate::Read<string>();
        while (!clsCurrency::IsCurrencyExist(CurrencyCode))
        {
            cout << "\nCurrency isn't found, Choose another one: ";
            CurrencyCode = clsInputValidate::Read<string>();
        }
        return CurrencyCode;
    }

    static clsCurrency _GetCurrency(string Massage)
    {
        cout << Massage;
        return clsCurrency::FindByCode(_ReadCurrencyCode());
    }

public:
    static void ShowCurrencyCalculatorScreen()
    {
        char Continue = 'Y';
        while (Continue == 'y' || Continue == 'Y')
        {
            system("cls");
            _DrawScreenHeader("Currency Calculator Screen");

            clsCurrency CurrencyFrom = _GetCurrency("\nPlease Enter Currency1 Code: ");
            clsCurrency CurrencyTo = _GetCurrency("\nPlease Enter Currency2 Code: ");
            float Amount = _ReadAmount();

            _PrintCalculationsResults(Amount, CurrencyFrom, CurrencyTo);

            cout << "\nDo you want to perform another Calculation? [y/n] ";
            Continue = clsInputValidate::Read<char>();
        }
    }
};
