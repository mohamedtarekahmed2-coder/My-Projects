#pragma once

#include <iostream>

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
};
