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
    static bool _Login()
    {
        bool LoginFail = false;
        string UserName, Password;
        int Trails = 3;
        do
        {
            if(LoginFail)
            {
                Trails--;
                if(!Trails)
                {
                    cout << "\nYou are Locked after 3 failed Trails\n";
                    return true;
                }
                cout << "\nInvalid User Name / Password!";
                cout << "\nYou have " << Trails << " Trail(s) to login.\n";
            }

            cout << "\nEnter User Name? ";
            cin >> UserName;

            cout << "\nEnter Password? ";
            cin >> Password;
            
            CurrentUser = clsUser::Find(UserName, Password);
            LoginFail = CurrentUser.IsEmpty();
        } while (LoginFail);

        CurrentUser.RegisterLogin();
        clsMainScreen::ShowMainMenu();
        return false;
    }
public:
    static bool ShowLoginScreen()
    {
        _DrawScreenHeader("Login Screen");
        return _Login();
    }
};

