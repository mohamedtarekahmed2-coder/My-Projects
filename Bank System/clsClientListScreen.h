#pragma once

#include <iostream>
#include <iomanip>
#include "clsBankClient.h"
#include "clsScreen.h"
using namespace std;

class clsClientListScreen : protected clsScreen
{
private:
    static void PrintClientRecordLine(clsBankClient Client)
    {
        cout << "| " << left << setw(15) << Client.GetAccountNumber();
        cout << "| " << left << setw(20) << Client.FullName();
        cout << "| " << left << setw(12) << Client.GetPhone();
        cout << "| " << left << setw(30) << Client.GetEmail();
        cout << "| " << left << setw(10) << Client.GetPinCode();
        cout << "| " << left << setw(12) << Client.GetAccountBalance();
    }

public:
    static void ShowClientsList()
    {
        vector<clsBankClient> vClient = clsBankClient::GetClientsList();

        string Title = "Client List Screen";
        string SubTitle = '(' + to_string((int)vClient.size()) + ") Client(s).";
        clsScreen::_DrawScreenHeader(Title, SubTitle);
        cout << "\n__________________________________________________________________________________________________________\n\n";
        cout << "| " << left << setw(15) << "Account Number";
        cout << "| " << left << setw(20) << "Client Name";
        cout << "| " << left << setw(12) << "Phone";
        cout << "| " << left << setw(30) << "Email";
        cout << "| " << left << setw(10) << "Pin Code";
        cout << "| " << left << setw(12) << "Balance";
        cout << "\n__________________________________________________________________________________________________________\n\n";
        if (vClient.size() == 0)
            cout << "No Data Exist";
        else
        {
            for (clsBankClient &Client : vClient)
            {
                PrintClientRecordLine(Client);
                cout << '\n';
            }
        }
        cout << "\n__________________________________________________________________________________________________________\n\n";
    }
};
