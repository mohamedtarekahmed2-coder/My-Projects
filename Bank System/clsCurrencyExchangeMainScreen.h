#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsCurrenciesListScreen.h"
#include "clsFindCurrencyScreen.h"
#include "clsUpdateCurrencyRateScreen.h"
#include "clsCurrencyCalculatorScreen.h"
using namespace std;

class clsCurrencyExchangeMainScreen : protected clsScreen
{
private:
    enum enCurrencyMainMenuOptions
    {
        eListCurrencies = 1,
        eFindCurrency,
        eUpdateCurrencyRate,
        eCurrencyCalculator,
        eMainMenu
    };

    static int _ReadCurrencyMainMenuOption()
    {
        cout << "Choose what do you want to do? [1 to 5]? ";
        return clsInputValidate::ReadNumberBetween<int>(0, 6, "Enter Number Between 1 to 5 ");
    }

    static void _GoBackToCurrencyMenu()
    {
        cout << "\n\nPress any key to go back to Currencies Menu...";
        system("pause>0");
        ShowCurrencyMenu();
    }

    static void _ShowCurrenciesListScreen()
    {
        // cout << "\nCurrencies List Screen Will Be Here.\n";
        clsCurrenciesListScreen::ShowCurrenciesListScreen();
    }

    static void _ShowFindCurrencyScreen()
    {
        // cout << "\nFind Currency Screen Will Be Here.\n";
        clsFindCurrencyScreen::ShowFindCurrencyScreen();
    }

    static void _ShowUpdateCurrencyRateScreen()
    {
        // cout << "\nUpdate Currency Rate Screen Will Be Here.\n";
        clsUpdateCurrencyRateScreen::ShowUpdateCurrencyRateScreen();
    }

    static void _ShowCurrencyCalculatorScreen()
    {
        // cout << "\nCurrency Calculator Screen Will Be Here.\n";
        clsCurrencyCalculatorScreen::ShowCurrencyCalculatorScreen();
    }

    static void _PerfromCurrencyMenuOption(enCurrencyMainMenuOptions CurrencyMenuOption)
    {
        switch (CurrencyMenuOption)
        {
        case enCurrencyMainMenuOptions::eListCurrencies:
            system("cls");
            _ShowCurrenciesListScreen();
            _GoBackToCurrencyMenu();
            break;

        case enCurrencyMainMenuOptions::eFindCurrency:
            system("cls");
            _ShowFindCurrencyScreen();
            _GoBackToCurrencyMenu();
            break;

        case enCurrencyMainMenuOptions::eUpdateCurrencyRate:
            system("cls");
            _ShowUpdateCurrencyRateScreen();
            _GoBackToCurrencyMenu();
            break;

        case enCurrencyMainMenuOptions::eCurrencyCalculator:
            system("cls");
            _ShowCurrencyCalculatorScreen();
            _GoBackToCurrencyMenu();
            break;

        case enCurrencyMainMenuOptions::eMainMenu:
            // do nothing here the main screen will handle it
            break;
        }
    }

public:
    static void ShowCurrencyMenu()
    {
        system("cls");
        _DrawScreenHeader("Currency Exchange Main Screen");

        cout << "===========================================\n";
        cout << "Currency Exchange Menu\n";
        cout << "===========================================\n";
        cout << "[1] List Currencies.\n";
        cout << "[2] Find Currency.\n";
        cout << "[3] Update Rate.\n";
        cout << "[4] Currency Calculator.\n";
        cout << "[5] Main Menu.\n";
        cout << "===========================================\n";
        _PerfromCurrencyMenuOption((enCurrencyMainMenuOptions)_ReadCurrencyMainMenuOption());
    }
};
