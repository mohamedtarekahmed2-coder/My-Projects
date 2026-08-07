#pragma once

#include <iostream>
#include <iomanip>
#include "clsUser.h"
#include "clsInputValidate.h"
#include "clsScreen.h"
using namespace std;

class clsDeleteUserScreen : protected clsScreen
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
    static void ShowDeleteUserScreen()
    {
        _DrawScreenHeader("Delete User Screen");
        cout << "\nPlease Enter User Name : ";
        string UserName = clsInputValidate::Read<string>();
        while (!clsUser::IsUserExist(UserName))
        {
            cout << "User Name isn't found, Choose another one : ";
            UserName = clsInputValidate::Read<string>();
        }

        clsUser User = clsUser::Find(UserName);
        _PrintUser(User);

        cout << "\nAre you sure you want to delete this User ? [y/n] ";
        char Answer = 'n';
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            if (User.Delete())
            {
                cout << "\nUser Deleted Successfully ";
                // _PrintUser(User);
            }
            else
            {
                cout << "\nError User wasn't Deleted\n";
            }
        }
    }
};
