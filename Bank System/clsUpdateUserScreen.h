#pragma once

#include <iostream>
#include <iomanip>
#include "clsUser.h"
#include "clsInputValidate.h"
#include "clsScreen.h"
using namespace std;

class clsUpdateUserScreen : protected clsScreen
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
    static void ShowUpdateUserScreen()
    {
        _DrawScreenHeader("Update User Screen");

        cout << "\nPlease Enter User Name : ";
        string UserName = clsInputValidate::Read<string>();

        while (!clsUser::IsUserExist(UserName))
        {
            cout << "\nUser Name isn't fount, choose anther one : ";
            UserName = clsInputValidate::Read<string>();
        }

        clsUser User = clsUser::Find(UserName);

        _PrintUser(User);

        cout << "Are you sure you want to update this User ? [y/n] ";
        char Answer;
        cin >> Answer;
        if (Answer == 'n' || Answer == 'N')
            return;

        cout << "\n\nUpdate User Info : ";
        cout << "\n_____________________\n";

        _ReadUserInfo(User);

        clsUser::enSaveResults SaveResult = User.Save();

        switch (SaveResult)
        {
        case clsUser::enSaveResults::svSucceeded:
        {
            cout << "\nAccount Updated Successfully :-)\n";
            // _PrintUser(User);
            break;
        }
        case clsUser::enSaveResults::svFailEmptyObject:
        {
            cout << "\nError account was not saved because it's Empty";
            break;
        }
        }
    }
};
