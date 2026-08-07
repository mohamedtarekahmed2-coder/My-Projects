#pragma once

#include <iostream>
#include <iomanip>
#include "clsInputValidate.h"
#include "clsScreen.h"
#include "clsMainScreen.h"
#include "Global.h"

using namespace std;

class clsLoginScreen : protected clsScreen
{
private:
    static void _Login()
    {
        bool LoginFail = false;
        string UserName, Password;

        do
        {
            if(LoginFail) 
                cout << "\nInvalid User Name / Password!";

            cout << "\nEnter User Name? ";
            cin >> UserName;

            cout << "\nEnter Password? ";
            cin >> Password;
            
            CurrentUser = clsUser::Find(UserName, Password);
            LoginFail = CurrentUser.IsEmpty();
        } while (LoginFail);

        clsMainScreen::ShowMainMenu();
    }
public:
    static void ShowLoginScreen()
    {
        _DrawScreenHeader("Login Screen");
        _Login();
    }
};

