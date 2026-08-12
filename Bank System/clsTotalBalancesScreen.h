#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include <iomanip>
#include "clsUtil.h"

using namespace std;

class clsTotalBalancesScreen : protected clsScreen
{
private:
    static void _PrintClientRecordBalanceLine(clsBankClient Client)
    {
        cout << "| " << left << setw(15) << Client.GetAccountNumber();
        cout << "| " << left << setw(30) << Client.GetFullName();
        cout << "| " << left << setw(12) << Client.GetAccountBalance();
    }
    
public:
    static void ShowTotalBalances()
    {
        vector<clsBankClient> vClients = clsBankClient::GetClientsList();

        string Title = "Balances List Screen";
        string SubTitle = '(' + to_string((int)vClients.size()) + ") Client(s).";
        _DrawScreenHeader(Title, SubTitle);

        cout << "\n_______________________________________________________________________\n\n";
        cout << "| " << left << setw(15) << "Account Number";
        cout << "| " << left << setw(30) << "Client Name";
        cout << "| " << left << setw(12) << "Balance";
        cout << "\n_______________________________________________________________________\n\n";
        if(vClients.size() == 0)
            cout << "\t\t\t\t No Clients Available In ";
        else 
        {
            for(clsBankClient &Client : vClients)
            {
                _PrintClientRecordBalanceLine(Client);
                cout << '\n';
            }
        }
        cout << "\n_______________________________________________________________________\n\n";
    
        double TotalBalances = clsBankClient::GetTotalBalances();
        cout << "Total Balances = " << fixed << setprecision(2) << TotalBalances << endl;
        cout << "( " << clsUtil::NumberToText(TotalBalances) << ")";
    }
};

