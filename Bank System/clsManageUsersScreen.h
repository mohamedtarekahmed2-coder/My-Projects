#pragma once

#include <iostream>
#include "clsInputValidate.h"
#include "clsScreen.h"
#include "clsListUsersScreen.h"
#include "clsAddNewUserScreen.h"
#include "clsDeleteUserScreen.h"
#include "clsUpdateUserScreen.h"
#include "clsFindUserScreen.h"

using namespace std;

class clsManageUsersScreen : protected clsScreen
{
private:
    enum enManageUsersMenuOptions
    {
        eListUsers = 1,
        eAddNewUser,
        eDeleteUser,
        eUpdateUser,
        eFindUser,
        eMainMenu
    };

    static void _GoBackToManageUsersMenu()
    {
        cout << "\nPress any key to go back to Manage Users Menu...\n";
        system("pause>0");
        ShowManageUsersMenu();
    }

    static int _ReadManageUsersMenuOption()
    {
        cout << "Choose what do you want to do? [1 to 6]? ";
        return clsInputValidate::ReadNumberBetween<int>(0, 7, "Enter Number Between 1 to 6 ");
    }

    static void _ShowListUsersScreen()
    {
        // cout << "\nList Users Screen Will Be Here.\n";
        clsListUsersScreen::ShowUsersList();
    }

    static void _ShowAddNewUserScreen()
    {
        // cout << "\nAdd New User Screen Will Be Here.\n";
        clsAddNewUserScreen::ShowAddNewUserScreen();
    }

    static void _ShowDeleteUserScreen()
    {
        // cout << "\nDelete User Screen Will Be Here.\n";
        clsDeleteUserScreen::ShowDeleteUserScreen();
    }

    static void _ShowUpdateUserScreen()
    {
        // cout << "\nUpdate User Screen Will Be Here.\n";
        clsUpdateUserScreen::ShowUpdateUserScreen();
    }

    static void _ShowFindUserScreen()
    {
        // cout << "\nFind User Screen Will Be Here.\n";
        clsFindUserScreen::ShowFindUserScreen();
    }

    static void _PerfromManageUsersMenuOption(enManageUsersMenuOptions ManageUsersMenuOption)
    {
        switch (ManageUsersMenuOption)
        {
        case enManageUsersMenuOptions::eListUsers:
            system("cls");
            _ShowListUsersScreen();
            _GoBackToManageUsersMenu();
            break;
        case enManageUsersMenuOptions::eAddNewUser:
            system("cls");
            _ShowAddNewUserScreen();
            _GoBackToManageUsersMenu();
            break;
        case enManageUsersMenuOptions::eDeleteUser:
            system("cls");
            _ShowDeleteUserScreen();
            _GoBackToManageUsersMenu();
            break;
        case enManageUsersMenuOptions::eUpdateUser:
            system("cls");
            _ShowUpdateUserScreen();
            _GoBackToManageUsersMenu();
            break;
        case enManageUsersMenuOptions::eFindUser:
            system("cls");
            _ShowFindUserScreen();
            _GoBackToManageUsersMenu();
            break;
        case enManageUsersMenuOptions::eMainMenu:
            // Do nothing here the main screen will handle it
            break;
        }
    }

public:
    static void ShowManageUsersMenu()
    {
        system("cls");
        _DrawScreenHeader("Manage Users Screen");

        cout << "===========================================\n";
        cout << "Manage Users Menu\n";
        cout << "===========================================\n";
        cout << "[1] List Users.\n";
        cout << "[2] Add New User.\n";
        cout << "[3] Delete User.\n";
        cout << "[4] Update User.\n";
        cout << "[5] Find User.\n";
        cout << "[6] Main Menu.\n";
        cout << "===========================================\n";

        _PerfromManageUsersMenuOption((enManageUsersMenuOptions)_ReadManageUsersMenuOption());
    }
};
