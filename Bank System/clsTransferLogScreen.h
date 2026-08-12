#pragma once

#include <iostream>
#include <iomanip>
#include "clsBankClient.h"
#include "clsScreen.h"
using namespace std;

class clsTransferLogScreen : protected clsScreen
{
private:
    static void PrintTransferLogRecordLine(clsBankClient::stTransferLogRecord TransferLogRecord)
    {
        cout << "| " << left << setw(30) << TransferLogRecord.DateTime;
        cout << "| " << left << setw(10) << TransferLogRecord.SourceAccountNumber;
        cout << "| " << left << setw(10) << TransferLogRecord.DestinationAccountNumber;
        cout << "| " << left << setw(12) << TransferLogRecord.Amount;
        cout << "| " << left << setw(12) << TransferLogRecord.srcBalanceAfter;
        cout << "| " << left << setw(12) << TransferLogRecord.destBalanceAfter;
        cout << "| " << left << setw(10) << TransferLogRecord.UserName;
    }

public:
    static void ShowTransferLogScreen()
    {
        vector<clsBankClient::stTransferLogRecord> vTransferLogRecord = clsBankClient::GetTransferLogList();

        string Title = "Transfer Log List Screen";
        string SubTitle = '(' + to_string((int)vTransferLogRecord.size()) + ") Record(s).";
        clsScreen::_DrawScreenHeader(Title, SubTitle);

        cout << "\n__________________________________________________________________________________________________________\n\n";
        cout << "| " << left << setw(30) << "Date/Time";
        cout << "| " << left << setw(10) << "s.Acct";
        cout << "| " << left << setw(10) << "d.Acct";
        cout << "| " << left << setw(12) << "Amount";
        cout << "| " << left << setw(12) << "s.Balance";
        cout << "| " << left << setw(12) << "d.Balance";
        cout << "| " << left << setw(10) << "User";
        cout << "\n__________________________________________________________________________________________________________\n\n";
        if (vTransferLogRecord.size() == 0)
            cout << "No Data Exist";
        else
        {
            for (clsBankClient::stTransferLogRecord &Record : vTransferLogRecord)
            {
                PrintTransferLogRecordLine(Record);
                cout << '\n';
            }
        }
        cout << "\n__________________________________________________________________________________________________________\n\n";
    }
};
