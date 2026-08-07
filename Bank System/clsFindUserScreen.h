#pragma once

#include <iostream>
#include <iomanip>
#include "clsUser.h"
#include "clsInputValidate.h"
#include "clsScreen.h"

class clsFindUserScreen : protected clsScreen
{
private:
    static void _PrintUser(clsUser User)
    {
        cout << "\nUser card:";
        cout << "\n____________________________";
        cout << "\nFirst Name  : " << User.GetFirstName();
        cout << "\nLast Name   : " << User.GetLastName();
        cout << "\nEmail       : " << User.GetEmail();
        cout << "\nPhone       : " << User.GetPhone();
        cout << "\nUser Name   : " << User.GetUserName();
        cout << "\nPassword    : " << User.GetPhone();
        cout << "\nPermissions : " << User.GetPermissions();
        cout << "\n____________________________\n";
    }


public:
    static void ShowFindUserScreen()
    {
        _DrawScreenHeader("Find User Screen");

        cout << "Please Enter User Name: ";
        string UserName = clsInputValidate::Read<string>();

        while (!clsUser::IsUserExist(UserName))
        {
            cout << "\nUser Name isn't found, Choose another one: ";
            UserName = clsInputValidate::Read<string>();
        }

        clsUser User = clsUser::Find(UserName);
        
        if (User.IsEmpty())
            cout << "\nUser Wan't Found\n";
        else
        {
            cout << "\nUser Found\n";
            _PrintUser(User);
        }
    }
};
