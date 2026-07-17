#pragma once

#include <iostream>
#include <string>
#include <limits>
#include <vector>

using namespace std;

class clsInputValidate
{
private:
public:
    template <typename ty>
    static bool IsNumberBetween(ty target, ty start, ty end)
    {
        return (start < target && target < end);
    }

    template <typename ty>
    static ty ReadNumber(string invalid)
    {
        ty num;
        while (true)
        {
            cin >> num;
            if (cin)
                return num;

            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << invalid << '\n';
        }
    }

    template <typename ty>
    static ty ReadNumberBetween(int start, int end, string invalid)
    {
        ty num;
        while (true)
        {
            cin >> num;
            if (cin && start < num && num < end)
                return num;

            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << invalid << '\n';
        }
    }

    template <typename ty>
    static vector<ty> ReadVector(int size, string invalid)
    {
        vector<ty> v(size);
        ty one_input;

        for (int i = 0; i < size; i++)
        {
            cin >> one_input;
            if (cin)
                v[i] = one_input;
            else
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                cout << invalid << '\n';
                i--;
                cout << i << '\n';
            }
        }
        return v;
    }
};
