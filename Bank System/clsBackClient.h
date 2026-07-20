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

    enMode mode;
    string account_number, PIN_code;
    float account_balance;

    static clsBackClient _ConvertLineToClientObject(string line, string Separator = "#//#")
    {
        vector<string> vClientData = clsString::Split(line, Separator);

        return clsBackClient(enMode::UpdateMode, vClientData[0], vClientData[1], vClientData[2], vClientData[3], vClientData[4], vClientData[5], stod(vClientData[6]));
    }

    static clsBackClient _GetEmptyClientObject()
    {
        return (clsBackClient(enMode::EmptyMode, "", "", "", "", "", "", 0));
    }

public:
    // Constructors
    clsBackClient(enMode mode, const string &first_name, const string &last_name, const string &email, const string &phone, const string &account_number, const string &PIN_code, float account_balance)
        : mode(mode), clsPerson(first_name, last_name, email, phone), account_number(account_number), PIN_code(PIN_code), account_balance(account_balance) {}

    // Getters & Setters
    bool IsEmpty()
    {
        return (mode == enMode::EmptyMode);
    }

    string get_account_number()
    {
        return account_number;
    }

    void set_PIN_code(const string &PIN_code_)
    {
        PIN_code = PIN_code_;
    }
    string get_PIN_code()
    {
        return PIN_code;
    }

    void set_account_balance(float balance)
    {
        account_balance = balance;
    }
    float get_account_balance()
    {
        return account_balance;
    }

    // Methods
    void Print()
    {
        cout << "\nClient card:";
        cout << "\n____________________________";
        cout << "\nName        : " << full_name();
        cout << "\nEmail       : " << get_email();
        cout << "\nPhone       : " << get_phone();
        cout << "\nAcc. Number : " << account_number;
        cout << "\nPassword    : " << PIN_code;
        cout << "\nBalance     : " << account_balance;
        cout << "\n____________________________\n";
    }
    
    static clsBackClient Find(string account_number)
    {
        vector<clsBackClient> vClients;

        fstream MyFile;
        MyFile.open("Clients.txt", ios::in);

        if(MyFile.is_open())
        {
            string line;
            while (getline(MyFile, line))
            {
                clsBackClient Client = _ConvertLineToClientObject(line);
                if(Client.account_number == account_number)
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
    static clsBackClient Find(string account_number, string PIN_code)
    {
        vector<clsBackClient> vClients;

        fstream MyFile;
        MyFile.open("Clients.txt", ios::in);

        if(MyFile.is_open())
        {
            string line;
            while (getline(MyFile, line))
            {
                clsBackClient Client = _ConvertLineToClientObject(line);
                if(Client.account_number == account_number && Client.PIN_code == PIN_code)
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

    static bool IsClientExist(string AccountNumber)
    {
        clsBackClient Client1 = clsBackClient::Find(AccountNumber);
        return (!Client1.IsEmpty());
    }
};
