#pragma once

#include <iostream>
#include <iomanip>
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "clsScreen.h"

class clsFindClientScreen : protected clsScreen
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
    static void ShowFindClientScreen()
    {
        _DrawScreenHeader("Find Client Screen");

        cout << "Please Enter Account Number: ";
        string AccountNumber = clsInputValidate::Read<string>();

        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nAccount Number isn't found, Choose another one: ";
            AccountNumber = clsInputValidate::Read<string>();
        }

        clsBankClient Client = clsBankClient::Find(AccountNumber);
        
        if (Client.IsEmpty())
            cout << "\nClient Wan't Found\n";
        else
        {
            cout << "\nClient Found\n";
            _PrintClient(Client);
        }
    }
};
