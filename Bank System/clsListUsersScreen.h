#pragma once

#include <iostream>
#include <iomanip>
#include "clsUser.h"
#include "clsScreen.h"
using namespace std;

class clsListUserScreen : protected clsScreen
{
private:
    static void PrintUserRecordLine(clsUser User)
    {
        cout << "| " << left << setw(10) << User.GetUserName();
        cout << "| " << left << setw(20) << User.GetFullName();
        cout << "| " << left << setw(12) << User.GetPhone();
        cout << "| " << left << setw(30) << User.GetEmail();
        cout << "| " << left << setw(10) << User.GetPassword();
        cout << "| " << left << setw(12) << User.GetPermissions();
    }

public:
    static void ShowUsersList()
    {
        vector<clsUser> vUsers = clsUser::GetUsersList();

        string Title = "User List Screen";
        string SubTitle = '(' + to_string((int)vUsers.size()) + ") User(s).";
        clsScreen::_DrawScreenHeader(Title, SubTitle);
        cout << "\n__________________________________________________________________________________________________________\n\n";
        cout << "| " << left << setw(10) << "User Name";
        cout << "| " << left << setw(20) << "Full Name";
        cout << "| " << left << setw(12) << "Phone";
        cout << "| " << left << setw(30) << "Email";
        cout << "| " << left << setw(10) << "Password";
        cout << "| " << left << setw(12) << "Permissions";
        cout << "\n__________________________________________________________________________________________________________\n\n";
        if (vUsers.size() == 0)
            cout << "No Data Exist";
        else
        {
            for (clsUser &User : vUsers)
            {
                PrintUserRecordLine(User);
                cout << '\n';
            }
        }
        cout << "\n__________________________________________________________________________________________________________\n\n";
    }
};
