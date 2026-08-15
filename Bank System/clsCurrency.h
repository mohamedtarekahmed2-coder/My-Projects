#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "clsString.h"

using namespace std;

class clsCurrency
{
private:
    enum enMode
    {
        EmptyMode,
        UpdateMode
    };

    enMode _Mode;
    string _Country;
    string _CurrencyCode;
    string _CurrencyName;
    float _Rate;

    static clsCurrency _ConvertLineToCurrencyObject(string Line, string Separator = "#//#")
    {
        vector<string> vCurrencyData = clsString::Split(Line, Separator);

        return clsCurrency(enMode::UpdateMode, vCurrencyData[0], vCurrencyData[1], vCurrencyData[2], stod(vCurrencyData[3]));
    }

    static vector<clsCurrency> _LoadCurrencysDataFromFile()
    {
        vector<clsCurrency> vCurrencys;
        fstream MyFile;
        MyFile.open("Currencies.txt", ios::in); // read mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                if (Line != "")
                {
                    clsCurrency Currency = _ConvertLineToCurrencyObject(Line);
                    vCurrencys.push_back(Currency);
                }
            }
            MyFile.close();
        }
        return vCurrencys;
    }

    static string _ConvertCurrencyObjectToLine(clsCurrency Currency, string Separator = "#//#")
    {
        string stCurrencyRecord = "";

        stCurrencyRecord += Currency._Country + Separator;
        stCurrencyRecord += Currency._CurrencyCode + Separator;
        stCurrencyRecord += Currency._CurrencyName + Separator;
        stCurrencyRecord += to_string(Currency._Rate);

        return stCurrencyRecord;
    }

    static void _SaveCurrencyDataToFile(vector<clsCurrency> _vCurrencys)
    {
        fstream MyFile;
        MyFile.open("Currencies.txt", ios::out); // overwrite
        string DataLine;
        if (MyFile.is_open())
        {
            for (clsCurrency Currency : _vCurrencys)
            {
                DataLine = _ConvertCurrencyObjectToLine(Currency);
                MyFile << DataLine << '\n';
            }
            MyFile.close();
        }
    }

    void _Update()
    {
        vector<clsCurrency> vCurrency = _LoadCurrencysDataFromFile();
        for (clsCurrency &C : vCurrency)
        {
            if (C._CurrencyCode == _CurrencyCode)
            {
                C = *this;
                break;
            }
        }
        _SaveCurrencyDataToFile(vCurrency);
    }

    static clsCurrency _GetEmptyCurrencyObject()
    {
        return clsCurrency(enMode::EmptyMode, "", "", "", 0);
    }

public:
    clsCurrency(enMode Mode, string Country, string CurrencyCode, string CurrencyName, float Rate)
    {
        _Mode = Mode;
        _Country = Country;
        _CurrencyCode = CurrencyCode;
        _CurrencyName = CurrencyName;
        _Rate = Rate;
    }

    bool IsEmpty()
    {
        return (_Mode == enMode::EmptyMode);
    }

    string Country()
    {
        return _Country;
    }

    string CurrencyCode()
    {
        return _CurrencyCode;
    }

    string CurrencyName()
    {
        return _CurrencyName;
    }

    float Rate()
    {
        return _Rate;
    }

    void UpdateRate(float NewRate)
    {
        _Rate = NewRate;
        _Update();
    }

    static clsCurrency FindByCode(string CurrencyCode)
    {
        CurrencyCode = clsString::UpperAllString(CurrencyCode);

        vector<clsCurrency> vCurrency = _LoadCurrencysDataFromFile();
        for (clsCurrency &Currency: vCurrency)
        {
            if(Currency.CurrencyCode() == CurrencyCode)
            {
                return Currency;
            }
        }
        return _GetEmptyCurrencyObject();
    }

    static clsCurrency FindByCountry(string Country)
    {
        Country = clsString::UpperAllString(Country);

        vector<clsCurrency> vCurrency = _LoadCurrencysDataFromFile();
        for (clsCurrency &Currency: vCurrency)
        {
            if(clsString::UpperAllString(Currency.Country()) == Country)
            {
                return Currency;
            }
        }

        return _GetEmptyCurrencyObject();
    }

    static bool IsCurrencyExist(string CurrencyCode)
    {
        clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);
        return !Currency.IsEmpty();
    }

    static vector<clsCurrency> GetCurrenciesList()
    {
        return _LoadCurrencysDataFromFile();
    }

    static vector<clsCurrency> GetAllUSDRates()
    {
        return _LoadCurrencysDataFromFile();
    }
};