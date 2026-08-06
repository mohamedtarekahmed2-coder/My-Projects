#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsDepositScreen.h"
#include "clsWithdrawScreen.h"
#include "clsTotalBalancesScreen.h"

using namespace std;

class clsTransactionsScreen : protected clsScreen
{
private:
    enum enTransactionsMenuOptions
    {
        eDeposit = 1,
        eWithdraw,
        eShowTotalBalance,
        eShowMainMenu
    };

    static int _ReadTransactionsMenuOption()
    {
        cout << "Choose what do you want to do? [1 to 4]? ";
        return clsInputValidate::ReadNumberBetween<int>(0, 5, "Enter Number Between 1 to 4 ");
    }

    static void _ShowDepositScreen()
    {
        // cout << "\n Deposit Screen will be here.\n";
        clsDepositScreen::ShowDepositScreen();
    }

    static void _ShowWithdrawScreen()
    {
        // cout << "\n Withdraw Screen will be here.\n";
        clsWithdrawScreen::ShowWithdrawScreen();
    }

    static void _ShowTotalBalancesScreen()
    {
        // cout << "\n Balances Screen will be here.\n";
        clsTotalBalancesScreen::ShowTotalBalances();
    }

    static void _GoBackToTransactionsMenu()
    {
        cout << "\n\nPress any key to go back to Transactions Menu...";
        system("pause>0");
        ShowTransactionsMenu();
    }

    static void _PerfromMainMenuOption(enTransactionsMenuOptions TransactionsMenuOption)
    {
        switch (TransactionsMenuOption)
        {
        case enTransactionsMenuOptions::eDeposit:
            system("cls");
            _ShowDepositScreen();
            _GoBackToTransactionsMenu();
            break;
        case enTransactionsMenuOptions::eWithdraw:
            system("cls");
            _ShowWithdrawScreen();
            _GoBackToTransactionsMenu();
            break;
        case enTransactionsMenuOptions::eShowTotalBalance:
            system("cls");
            _ShowTotalBalancesScreen();
            _GoBackToTransactionsMenu();
            break;
        case enTransactionsMenuOptions::eShowMainMenu:
            //do nothing here the main screen will handle it 
            break;
        }
    }

public:
    static void ShowTransactionsMenu()
    {
        system("cls");
        _DrawScreenHeader("Transactions Screen");

        cout << "===========================================\n";
        cout << "Transactions Menu\n";
        cout << "===========================================\n";
        cout << "[1] Deposit.\n";
        cout << "[2] Withdraw.\n";
        cout << "[3] Total Balances.\n";
        cout << "[4] Main Menu.\n";
        cout << "===========================================\n";
        _PerfromMainMenuOption((enTransactionsMenuOptions)_ReadTransactionsMenuOption());
    }
};
