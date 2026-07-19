#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "clsString.h"
#include "clsDate.h"

using namespace std;

class clsInputValidate
{
private:
    static bool FromIsAfterTo(clsDate from, clsDate to)
    {
        if (clsDate::IsDate1AfterDate2(from, to))
            return true;
        
        return false;
    }

public:
    template <typename ty>
    static bool IsNumberBetween(ty date, ty start, ty end)
    {
        return (start < date && date < end);
    }

    static bool IsDateBetween(clsDate date, clsDate from, clsDate to)
    {
        if (FromIsAfterTo(from, to))
            clsDate::SwapDates(from, to);

        if (clsDate::IsDate1BeforeDate2(from, date) && clsDate::IsDate1AfterDate2(to, date))
            return true;

        return false;
    }

    template <typename ty>
    static ty ReadNumber(string invalid = "Invalid Number, Enter again : ")
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
    static ty ReadNumberBetween(ty start, ty end, string invalid)
    {
        ty num;
        while (true)
        {
            cin >> num;
            if (cin && IsDateBetween(num, start, end))
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
