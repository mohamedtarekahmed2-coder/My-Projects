#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include <climits>
using namespace std;

class clsTransferScreen : protected clsScreen
{
private:
    static void _PrintClient(clsBankClient Client)
    {
        cout << "\nClient card:";
        cout << "\n____________________________";
        cout << "\nFull Name   : " << Client.GetFullName();
        cout << "\nAcc. Number : " << Client.GetAccountNumber();
        cout << "\nBalance     : " << Client.GetAccountBalance();
        cout << "\n____________________________\n";
    }

    static string _ReadAccountNumber(string from_to)
    {
        cout << "Please enter AccountNumber to Transfer " << from_to << ": ";
        string AccountNumber = clsInputValidate::Read<string>();

        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nAccount number is not found, choose another one: ";
            AccountNumber = clsInputValidate::Read<string>();
        }

        return AccountNumber;
    }

    static float ReadAmount(clsBankClient &SourceClient)
    {
        cout << "\nEnter Transfer Amount? ";
        float Amount = clsInputValidate::Read<float>();
        while(Amount <= 0)
        {
            cout << "\nHahahaha Not Now, Enter another Amount? ";
            Amount = clsInputValidate::Read<float>();
        }
        while(Amount > SourceClient.GetAccountBalance())
        {
            cout << "\nAmount Exceeds the available balance, Enter another Amount? ";
            Amount = clsInputValidate::Read<float>();
        }
        return Amount;
    }

public:
    static void ShowTransferScreen()
    {
        _DrawScreenHeader("Transfer Screen");

        clsBankClient SourceClient = clsBankClient::Find(_ReadAccountNumber("from"));
        _PrintClient(SourceClient);
        clsBankClient DestinationClient = clsBankClient::Find(_ReadAccountNumber("to"));
        _PrintClient(DestinationClient);

        float Amount = ReadAmount(SourceClient);

        cout << "\nAre you sure want to perform this operation? [y/n] ";
        char Answer = clsInputValidate::Read<char>();
        
        if(Answer == 'y' || Answer == 'Y')
        {
            if( SourceClient.Transfer(Amount, DestinationClient))
            {
                cout << "\nTransfer done successfully.\n";
            }
            else 
            {
                cout << "\nTransfer Failed.\n";
            }
        }

        _PrintClient(SourceClient);
        _PrintClient(DestinationClient);
    }
};
