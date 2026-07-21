#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "clsPerson.h"
#include "clsString.h"

using namespace std;

class clsBackClient : public clsPerson
{
private:
    enum enMode
    {
        EmptyMode,
        UpdateMode
    };

    enMode _Mode;
    string AccountNumber, PIN_code;
    float AccountBalance;

    static clsBackClient _ConvertLineToClientObject(string line, string Separator = "#//#")
    {
        vector<string> vClientData = clsString::Split(line, Separator);

        return clsBackClient(enMode::UpdateMode, vClientData[0], vClientData[1], vClientData[2], vClientData[3], vClientData[4], vClientData[5], stod(vClientData[6]));
    }

    static string _ConvertClientObjectToLine(clsBackClient Client, string Separator = "#//#")
    {
        string stClientRecord = "";

        stClientRecord += Client.GetFirstName() + Separator;
        stClientRecord += Client.GetLastName() + Separator;
        stClientRecord += Client.GetEmail() + Separator;
        stClientRecord += Client.GetPhone() + Separator;
        stClientRecord += Client.AccountNumber + Separator;
        stClientRecord += Client.PIN_code + Separator;
        stClientRecord += to_string(Client.AccountBalance);

        return stClientRecord;
    }

    static clsBackClient _GetEmptyClientObject()
    {
        return (clsBackClient(enMode::EmptyMode, "", "", "", "", "", "", 0));
    }

    static vector<clsBackClient> _LoadClientsDataFromFile()
    {
        vector<clsBackClient> vClients;
        fstream MyFile;
        MyFile.open("Clients.txt", ios::in);

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsBackClient Client = _ConvertLineToClientObject(Line);
                vClients.push_back(Client);
            }

            MyFile.close();
        }
        return vClients;
    }

    void _Update()
    {
        vector<clsBackClient> _vClients = _LoadClientsDataFromFile();

        for (clsBackClient &Client : _vClients)
        {
            if (Client.AccountNumber == AccountNumber)
            {
                Client = *this;
                break;
            }
        }
        _SaveClientsDataToFile(_vClients);
    }

    void _SaveClientsDataToFile(vector<clsBackClient> vClients)
    {
        fstream MyFile;
        MyFile.open("Clients.txt", ios::out);
        string DataLine;
        if (MyFile.is_open())
        {
            for (clsBackClient Client : vClients)
            {
                DataLine = _ConvertClientObjectToLine(Client);
                MyFile << DataLine << '\n';
            }
            MyFile.close();
        }
    }

public:
    // Constructors
    clsBackClient(enMode mode, const string &first_name, const string &last_name, const string &email, const string &phone, const string &AccountNumber, const string &PIN_code, float AccountBalance)
        : _Mode(mode), clsPerson(first_name, last_name, email, phone), AccountNumber(AccountNumber), PIN_code(PIN_code), AccountBalance(AccountBalance) {}

    // Getters & Setters
    bool IsEmpty()
    {
        return (_Mode == enMode::EmptyMode);
    }

    string GetAccountNumber()
    {
        return AccountNumber;
    }

    void SetPinCode(const string &PIN_code_)
    {
        PIN_code = PIN_code_;
    }
    string get_PIN_code()
    {
        return PIN_code;
    }

    void SetAccountBalance(float balance)
    {
        AccountBalance = balance;
    }
    float get_account_balance()
    {
        return AccountBalance;
    }

    // Methods
    void Print()
    {
        cout << "\nClient card:";
        cout << "\n____________________________";
        cout << "\nFirst Name  : " << GetFirstName();
        cout << "\nLast Name   : " << GetLastName();
        cout << "\nEmail       : " << GetEmail();
        cout << "\nPhone       : " << GetPhone();
        cout << "\nAcc. Number : " << AccountNumber;
        cout << "\nPassword    : " << PIN_code;
        cout << "\nBalance     : " << AccountBalance;
        cout << "\n____________________________\n";
    }

    static clsBackClient Find(string AccountNumber)
    {
        vector<clsBackClient> vClients;

        fstream MyFile;
        MyFile.open("Clients.txt", ios::in);

        if (MyFile.is_open())
        {
            string line;
            while (getline(MyFile, line))
            {
                clsBackClient Client = _ConvertLineToClientObject(line);
                if (Client.AccountNumber == AccountNumber)
                {
                    MyFile.close();
                    return Client;
                }
                vClients.push_back(Client);
            }
            MyFile.close();
        }
        return _GetEmptyClientObject();
    }
    static clsBackClient Find(string AccountNumber, string PIN_code)
    {
        vector<clsBackClient> vClients;

        fstream MyFile;
        MyFile.open("Clients.txt", ios::in);

        if (MyFile.is_open())
        {
            string line;
            while (getline(MyFile, line))
            {
                clsBackClient Client = _ConvertLineToClientObject(line);
                if (Client.AccountNumber == AccountNumber && Client.PIN_code == PIN_code)
                {
                    MyFile.close();
                    return Client;
                }
                vClients.push_back(Client);
            }
            MyFile.close();
        }
        return _GetEmptyClientObject();
    }

    enum enSaveResults
    {
        svFailEmptyObject,
        svSucceeded
    };

    enSaveResults Save()
    {
        switch (_Mode)
        {
            case enMode::EmptyMode:
                return enSaveResults::svFailEmptyObject;
            case enMode::UpdateMode:
            {
                _Update();
                return enSaveResults::svSucceeded;
            }
        }
        return enSaveResults::svFailEmptyObject; 
    }

    static bool IsClientExist(string AccountNumber)
    {
        clsBackClient Client1 = clsBackClient::Find(AccountNumber);
        return (!Client1.IsEmpty());
    }
};
