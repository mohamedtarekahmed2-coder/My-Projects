#pragma once

#include <iostream>
#include <iomanip>
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "clsScreen.h"
using namespace std;

class clsAddNewClientScreen : protected clsScreen
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
    static void ShowAddNewClientScreen()
    {
        _DrawScreenHeader("Add New Client Screen");

        cout << "\nPlease Enter Account Number : ";
        string AccountNumber = clsInputValidate::Read<string>();
        while (clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "Account Number Is Already Used, Choose another one : ";
            AccountNumber = clsInputValidate::Read<string>();
        }

        clsBankClient NewClient = clsBankClient::GetAddNewClientObject(AccountNumber);
        _ReadClientInfo(NewClient);

        clsBankClient::enSaveResults SaveResult = NewClient.Save();
        switch (SaveResult)
        {
        case clsBankClient::enSaveResults::svSucceeded:
            cout << "\nAccount Added Successfully \n";
            _PrintClient(NewClient);
            break;
        case clsBankClient::enSaveResults::svFailEmptyObject:
            cout << "\nError Account wasn't saved because it's Empty \n";
            break;
        case clsBankClient::enSaveResults::svFailAccountNumberExists:
            cout << "\nError Account wasn't saved because Account Number is Used\n";
            break;
        }
    }
};
