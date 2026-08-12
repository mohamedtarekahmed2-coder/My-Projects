#pragma once

#include <iostream>
#include <iomanip>
#include "clsUser.h"
#include "clsScreen.h"
using namespace std;

class clsLoginRegisterScreen : protected clsScreen
{
private:
    static void PrintLogRecordLine(clsUser::stLoginRegisterRecord LoginRegisterRecord)
    {
        cout << "| " << left << setw(30) << LoginRegisterRecord.DateTime;
        cout << "| " << left << setw(10) << LoginRegisterRecord.UserName;
        cout << "| " << left << setw(10) << LoginRegisterRecord.Password;
        cout << "| " << left << setw(12) << LoginRegisterRecord.Permissions;
    }

public:
    static void ShowLoginRegisterScreen()
    {
        if(!CheckAccessRights(clsUser::enPermissions::pLoginRegister))
        {
            return;
        }

        vector<clsUser::stLoginRegisterRecord> vLoginRegisterRecord = clsUser::GetLoginRegisterList();

        string Title = "Login Register List Screen";
        string SubTitle = '(' + to_string((int)vLoginRegisterRecord.size()) + ") Record(s).";
        clsScreen::_DrawScreenHeader(Title, SubTitle);

        cout << "\n__________________________________________________________________________________________________________\n\n";
        cout << "| " << left << setw(30) << "Date/Time";
        cout << "| " << left << setw(10) << "User Name";
        cout << "| " << left << setw(10) << "Password";
        cout << "| " << left << setw(12) << "Permissions";
        cout << "\n__________________________________________________________________________________________________________\n\n";
        if (vLoginRegisterRecord.size() == 0)
            cout << "No Data Exist";
        else
        {
            for (clsUser::stLoginRegisterRecord &Record : vLoginRegisterRecord)
            {
                PrintLogRecordLine(Record);
                cout << '\n';
            }
        }
        cout << "\n__________________________________________________________________________________________________________\n\n";
    }
};
