#pragma once

#include <iostream>
#include <iomanip>
#include "clsUser.h"
#include "clsInputValidate.h"
#include "clsScreen.h"
using namespace std;

class clsAddNewUserScreen : protected clsScreen
{
private:
    static void _ReadUserInfo(clsUser &User)
    {
        cout << "Enter FirstName : ";
        User.SetFirstName(clsInputValidate::Read<string>());

        cout << "Enter LastName : ";
        User.SetLastName(clsInputValidate::Read<string>());

        cout << "Enter Email : ";
        User.SetEmail(clsInputValidate::Read<string>());

        cout << "Enter Phone : ";
        User.SetPhone(clsInputValidate::Read<string>());

        cout << "Enter Password : ";
        User.SetPassword(clsInputValidate::Read<string>());

        cout << "Enter Permission : ";
        User.SetPermissions(_ReadPermissionsToSet());

        system("cls");
    }

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

    static int _ReadPermissionsToSet()
    {
        int Permissions = 0;
        char Answer = 'n';

        cout << "\nDo you want to give full access? [y/n] ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
            return -1;

        cout << "\nDo you want to give access to : \n";

        cout << "\nShow Client List? [y/n] ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
            Permissions += clsUser::enPermissions::pListClients;

        cout << "\nAdd New Client? [y/n] ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
            Permissions += clsUser::enPermissions::pAddNewClient;

        cout << "\nDelete Client? [y/n] ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
            Permissions += clsUser::enPermissions::pDeleteClient;

        cout << "\nUpdate Client? [y/n] ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
            Permissions += clsUser::enPermissions::pUpdateClients;

        cout << "\nFind Client? [y/n] ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
            Permissions += clsUser::enPermissions::pFindClient;

        cout << "\nTransactions? [y/n] ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
            Permissions += clsUser::enPermissions::pTransactions;

        cout << "\nManage Users? [y/n] ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
            Permissions += clsUser::enPermissions::pManageUsers;

        cout << "\nLogin Register? [y/n] ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
            Permissions += clsUser::enPermissions::pLoginRegister;

        return Permissions;
    }

public:
    static void ShowAddNewUserScreen()
    {
        _DrawScreenHeader("Add New User Screen");

        cout << "\nPlease Enter User Name : ";
        string UserName = clsInputValidate::Read<string>();
        while (clsUser::IsUserExist(UserName))
        {
            cout << "User Name Is Already Used, Choose another one : ";
            UserName = clsInputValidate::Read<string>();
        }

        clsUser NewUser = clsUser::GetAddNewUserObject(UserName);
        _ReadUserInfo(NewUser);

        clsUser::enSaveResults SaveResult = NewUser.Save();
        switch (SaveResult)
        {
        case clsUser::enSaveResults::svSucceeded:
            cout << "\nAccount Added Successfully \n";
            _PrintUser(NewUser);
            break;
        case clsUser::enSaveResults::svFailEmptyObject:
            cout << "\nError Account wasn't saved because it's Empty \n";
            break;
        case clsUser::enSaveResults::svFailUserExists:
            cout << "\nError Account wasn't saved because User Name is Used\n";
            break;
        }
    }
};
