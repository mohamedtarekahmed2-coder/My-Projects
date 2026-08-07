#pragma once

#include <iostream>
#include <iomanip>
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "clsScreen.h"
using namespace std;

class clsUpdateClientScreen : protected clsScreen
{
private:
    static void _ReadClientInfo(clsBankClient &Client)
    {
        cout << "Enter FirstName : ";
        Client.SetFirstName(clsInputValidate::Read<string>());

        cout << "Enter LastName : ";
        Client.SetLastName(clsInputValidate::Read<string>());

        cout << "Enter Email : ";
        Client.SetEmail(clsInputValidate::Read<string>());

        cout << "Enter Phone : ";
        Client.SetPhone(clsInputValidate::Read<string>());

        cout << "Enter PinCode : ";
        Client.SetPinCode(clsInputValidate::Read<string>());

        cout << "Enter Account Balance : ";
        Client.SetAccountBalance(clsInputValidate::Read<float>());

        system("cls");
    }

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
    static void ShowUpdateClientScreen()
    {
        if(!CheckAccessRights(clsUser::enPermissions::pUpdateClients))
        {
            return;
        }
        
        _DrawScreenHeader("Update Client Screen");

        cout << "\nPlease Enter Client Account Number : ";
        string AccountNumber = clsInputValidate::Read<string>();

        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nAccount Number isn't fount, choose anther one : ";
            AccountNumber = clsInputValidate::Read<string>();
        }

        clsBankClient Client = clsBankClient::Find(AccountNumber);

        _PrintClient(Client);

        cout << "Are you sure you want to update this Client ? [y/n] ";
        char answer;
        cin >> answer;
        if (answer == 'n' || answer == 'N')
            return;

        cout << "\n\nUpdate Client Info : ";
        cout << "\n_____________________\n";

        _ReadClientInfo(Client);

        clsBankClient::enSaveResults SaveResult = Client.Save();

        switch (SaveResult)
        {
        case clsBankClient::enSaveResults::svSucceeded:
        {
            cout << "\nAccount Updated Successfully :-)\n";
            // _PrintClient(Client);
            break;
        }
        case clsBankClient::enSaveResults::svFailEmptyObject:
        {
            cout << "\nError account was not saved because it's Empty";
            break;
        }
        }
    }
};
