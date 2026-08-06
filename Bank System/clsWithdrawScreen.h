#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"

class clsWithdrawScreen : protected clsScreen
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

    static string _ReadAccountNumber()
    {
        cout << "Please enter AccountNumber? ";
        return clsInputValidate::Read<string>();
    }

public:
    static void ShowWithdrawScreen()
    {
        _DrawScreenHeader("Withdraw Screen");

        string AccountNumber = _ReadAccountNumber();

        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nClient with [" << AccountNumber << "] does not exist.\n";
            AccountNumber = _ReadAccountNumber();
        }

        clsBankClient Client = clsBankClient::Find(AccountNumber);
        _PrintClient(Client);

        cout << "\nPlease enter Withdraw amount? ";
        float Amount = clsInputValidate::Read<float>();

        cout << "\nAre you sure you want to perform this transaction? [y/n] ";
        char Answer = clsInputValidate::Read<char>();
        
        if (Answer == 'y' | Answer == 'Y')
        {
            if(Client.Withdraw(Amount))
            {
                cout << "\nAmount Withdraw Successfully.\n";
                cout << "\nNew Balance Is: " << Client.GetAccountBalance();
            }
            else 
            {
                cout << "\nCan't withdraw, Insufficient Balance.\n";
                cout << "\nAmount to withdraw is: " << Amount;
                cout << "\nYour Balance is: " << Client.GetAccountBalance();
            }
        }
        else
        {
            cout << "\nOperation was cancelled.\n";
        }
    }
};
