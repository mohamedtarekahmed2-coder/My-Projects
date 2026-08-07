#pragma once

#include <iostream>
#include "clsUser.h"
#include "Global.h"

using namespace std;

class clsScreen
{
protected:
    static void _DrawScreenHeader(string Title, string SubTitle = "")
    {
        cout << "______________________________________";
        cout << "\n\n" << Title;
        if (SubTitle != "")
            cout << "\n" << SubTitle;
        cout << "\n______________________________________\n\n";
    }
    
    static bool CheckAccessRights(clsUser::enPermissions Permission)
    {
        if(CurrentUser.CheckAccessPermission(Permission))
        {
            return true;
        }
        else 
        {
            _DrawScreenHeader("Access Denied! Contact you admin");
            return false;
        }
        // return true;
    }
};
