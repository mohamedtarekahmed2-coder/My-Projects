#pragma once

#include <iostream>
#include "clsUser.h"
#include "Global.h"
#include "clsDate.h"

using namespace std;

class clsScreen
{
protected:
    static void _DrawScreenHeader(string Title, string SubTitle = "")
    {
        cout << "______________________________________";
        cout << "\n\n"
             << Title;
        if (SubTitle != "")
            cout << "\n"
                 << SubTitle;
        cout << "\n______________________________________\n\n";

        clsDate Date = clsDate::GetSystemDate();
        cout << "User: " << CurrentUser.GetUserName() << '\n';
        cout << "Date: " << clsDate::DateToString(clsDate()) << "\n\n";
    }

    static bool CheckAccessRights(clsUser::enPermissions Permission)
    {
        if (CurrentUser.CheckAccessPermission(Permission))
        {
            return true;
        }
        else
        {
            cout << "______________________________________\n\n";
            cout << "Access Denied! Contact you admin.";
            cout << "\n______________________________________\n\n";
            return false;
        }
        // return true;
    }
};
