#pragma once

#include <iostream>
#include <iomanip>
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "clsScreen.h"
using namespace std;

class clsDeleteClientScreen : protected clsScreen
{
private:
    static void _PrintClient(clsBankClient Client)
    {
        cout << "\nClient card:";
        cout << "\n____________________________";
        cout << "\nFirst Name  : " << Client.GetFirstName();
        cout << "\nLast Name   : " << Client.GetLastName();
        cout << "\nEmail       : " << Client.GetEmail();
        cout << "\nPhone       : " << Client.GetPhone();
        cout << "\nAcc. Number : " << Client.GetAccountNumber();
        cout << "\nPassword    : " << Client.GetPhone();
        cout << "\nBalance     : " << Client.GetAccountBalance();
        cout << "\n____________________________\n";
    }

public:
    static void ShowDeleteClientScreen()
    {
        if(!CheckAccessRights(clsUser::enPermissions::pDeleteClient))
        {
            return;
        }
        
        _DrawScreenHeader("Delete Client Screen");
        cout << "\nPlease Enter Account Number : ";
        string AccountNumber = clsInputValidate::Read<string>();
        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "Account Number isn't found, Choose another one : ";
            AccountNumber = clsInputValidate::Read<string>();
        }

        clsBankClient Client = clsBankClient::Find(AccountNumber);
        _PrintClient(Client);

        cout << "\nAre you sure you want to delete this Client ? [y/n] ";
        char Answer = 'n';
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            if (Client.Delete())
            {
                cout << "\nClient Deleted Successfully ";
                // _PrintClient(Client);
            }
            else
            {
                cout << "\nError Client wasn't Deleted\n";
            }
        }
    }
};
