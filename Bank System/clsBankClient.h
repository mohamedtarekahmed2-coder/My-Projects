#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "clsPerson.h"
#include "clsString.h"

using namespace std;

class clsBankClient : public clsPerson
{
public:
    struct stTransferLogRecord
    {
        string DateTime;
        string SourceAccountNumber;
        string DestinationAccountNumber;
        float Amount;
        float srcBalanceAfter;
        float destBalanceAfter;
        string UserName;
    };

private:
    enum enMode
    {
        EmptyMode,
        UpdateMode,
        AddNewMode
    };

    enMode _Mode;
    string _AccountNumber, _PIN_code;
    float _AccountBalance;
    bool _MarkedForDelete = false;

    static clsBankClient _ConvertLineToClientObject(string line, string Separator = "#//#")
    {
        vector<string> vClientData = clsString::Split(line, Separator);

        return clsBankClient(enMode::UpdateMode, vClientData[0], vClientData[1], vClientData[2], vClientData[3], vClientData[4], vClientData[5], stod(vClientData[6]));
    }

    static string _ConvertClientObjectToLine(clsBankClient Client, string Separator = "#//#")
    {
        string stClientRecord = "";

        stClientRecord += Client.GetFirstName() + Separator;
        stClientRecord += Client.GetLastName() + Separator;
        stClientRecord += Client.GetEmail() + Separator;
        stClientRecord += Client.GetPhone() + Separator;
        stClientRecord += Client._AccountNumber + Separator;
        stClientRecord += Client._PIN_code + Separator;
        stClientRecord += to_string(Client._AccountBalance);

        return stClientRecord;
    }

    static clsBankClient _GetEmptyClientObject()
    {
        return (clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0));
    }

    static vector<clsBankClient> _LoadClientsDataFromFile()
    {
        vector<clsBankClient> vClients;
        fstream MyFile;
        MyFile.open("Clients.txt", ios::in);

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                if (Line != "")
                {
                    clsBankClient Client = _ConvertLineToClientObject(Line);
                    vClients.push_back(Client);
                }
            }
            MyFile.close();
        }
        return vClients;
    }

    void _Update()
    {
        vector<clsBankClient> _vClients = _LoadClientsDataFromFile();

        for (clsBankClient &Client : _vClients)
        {
            if (Client._AccountNumber == _AccountNumber)
            {
                Client = *this;
                break;
            }
        }
        _SaveClientsDataToFile(_vClients);
    }

    void _SaveClientsDataToFile(vector<clsBankClient> vClients)
    {
        fstream MyFile;
        MyFile.open("Clients.txt", ios::out);
        string DataLine;
        if (MyFile.is_open())
        {
            for (clsBankClient Client : vClients)
            {
                if (Client._MarkedForDelete == false)
                {
                    DataLine = _ConvertClientObjectToLine(Client);
                    MyFile << DataLine << '\n';
                }
            }
            MyFile.close();
        }
    }

    void _AddNew()
    {
        _AddDataLineToFile(_ConvertClientObjectToLine(*this));
    }

    void _AddDataLineToFile(string stDataLine)
    {
        fstream MyFile;
        MyFile.open("Clients.txt", ios::out | ios::app);
        if (MyFile.is_open())
        {
            MyFile << stDataLine << '\n';
            MyFile.close();
        }
    }

    string _PrepareTransferLogRecord(float Amount, clsBankClient &DestinationClient, string Separator = "#//#")
    {
        string TransferLogRecord = "";
        TransferLogRecord += clsDate::GetSystemDateTimeString() + Separator;
        TransferLogRecord += _AccountNumber + Separator;
        TransferLogRecord += DestinationClient.GetAccountNumber() + Separator;
        TransferLogRecord += to_string(Amount) + Separator;
        TransferLogRecord += to_string(_AccountBalance) + Separator;
        TransferLogRecord += to_string(DestinationClient.GetAccountBalance()) + Separator;
        TransferLogRecord += CurrentUser.GetUserName() + '\n';
        return TransferLogRecord;
    }

    void _RegisterTransferLog(float Amount, clsBankClient &DestinationClient)
    {
        string stDataLine = _PrepareTransferLogRecord(Amount, DestinationClient);
        fstream myFile;
        myFile.open("TransferLog.txt", ios::out | ios::app);

        if (myFile.is_open())
        {
            myFile << stDataLine;
            myFile.close();
        }
    }

    static stTransferLogRecord _ConvertTransferLogLineToRecord(string Line, string Separator = "#//#")
    {
        vector<string> TransferLogDataLine = clsString::Split(Line, Separator);
        stTransferLogRecord TransferLogRecord;

        TransferLogRecord.DateTime = TransferLogDataLine[0];
        TransferLogRecord.SourceAccountNumber = TransferLogDataLine[1];
        TransferLogRecord.DestinationAccountNumber = TransferLogDataLine[2];
        TransferLogRecord.Amount = stoi(TransferLogDataLine[3]);
        TransferLogRecord.srcBalanceAfter = stoi(TransferLogDataLine[4]);
        TransferLogRecord.destBalanceAfter = stoi(TransferLogDataLine[5]);
        TransferLogRecord.UserName = TransferLogDataLine[6];

        return TransferLogRecord;
    }

public:
    // Constructors
    clsBankClient(enMode mode, string first_name, string last_name, string email, string phone, string AccountNumber, string PIN_code, float AccountBalance)
        : clsPerson(first_name, last_name, email, phone)
    {
        _Mode = mode;
        _AccountBalance = AccountBalance;
        _PIN_code = PIN_code;
        _AccountNumber = AccountNumber;
    }

    // Getters & Setters
    bool IsEmpty()
    {
        return (_Mode == enMode::EmptyMode);
    }

    string GetAccountNumber()
    {
        return _AccountNumber;
    }

    void SetPinCode(const string &PIN_code_)
    {
        _PIN_code = PIN_code_;
    }
    string GetPinCode()
    {
        return _PIN_code;
    }

    void SetAccountBalance(float balance)
    {
        _AccountBalance = balance;
    }
    float GetAccountBalance()
    {
        return _AccountBalance;
    }

    // Methods
    static clsBankClient Find(string AccountNumber)
    {
        vector<clsBankClient> vClients;

        fstream MyFile;
        MyFile.open("Clients.txt", ios::in);

        if (MyFile.is_open())
        {
            string line;
            while (getline(MyFile, line))
            {
                clsBankClient Client = _ConvertLineToClientObject(line);
                if (Client._AccountNumber == AccountNumber)
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
    static clsBankClient Find(string AccountNumber, string PIN_code)
    {
        vector<clsBankClient> vClients;

        fstream MyFile;
        MyFile.open("Clients.txt", ios::in);

        if (MyFile.is_open())
        {
            string line;
            while (getline(MyFile, line))
            {
                clsBankClient Client = _ConvertLineToClientObject(line);
                if (Client._AccountNumber == AccountNumber && Client._PIN_code == PIN_code)
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
        svSucceeded,
        svFailEmptyObject,
        svFailAccountNumberExists
    };

    enSaveResults Save()
    {
        switch (_Mode)
        {
        case enMode::EmptyMode:
        {
            if (IsEmpty())
            {
                return enSaveResults::svFailEmptyObject;
            }
            break;
        }
        case enMode::UpdateMode:
        {
            _Update();
            return enSaveResults::svSucceeded;
            break;
        }
        case enMode::AddNewMode:
        {
            if (clsBankClient::IsClientExist(_AccountNumber))
            {
                return enSaveResults::svFailAccountNumberExists;
            }
            else
            {
                _AddNew();
                _Mode = enMode::UpdateMode;
                return enSaveResults::svSucceeded;
            }
            break;
        }
        }
        return enSaveResults::svFailEmptyObject;
    }

    static bool IsClientExist(string AccountNumber)
    {
        clsBankClient Client1 = clsBankClient::Find(AccountNumber);
        return (!Client1.IsEmpty());
    }

    static clsBankClient GetAddNewClientObject(string AccountNumber)
    {
        return clsBankClient(enMode::AddNewMode, "", "", "", "", AccountNumber, "", 0);
    }

    bool Delete()
    {
        vector<clsBankClient> _vClients = _LoadClientsDataFromFile();

        for (clsBankClient &Client : _vClients)
        {
            if (Client._AccountNumber == _AccountNumber)
            {
                Client._MarkedForDelete = true;
                break;
            }
        }

        _SaveClientsDataToFile(_vClients);
        *this = _GetEmptyClientObject();
        return true;
    }

    static vector<clsBankClient> GetClientsList()
    {
        return _LoadClientsDataFromFile();
    }

    static double GetTotalBalances()
    {
        vector<clsBankClient> vClients = clsBankClient::GetClientsList();
        double TotalBalances = 0;
        for (clsBankClient &Client : vClients)
        {
            TotalBalances += Client.GetAccountBalance();
        }
        return TotalBalances;
    }

    void Deposit(float Amount)
    {
        _AccountBalance += Amount;
        Save();
    }

    bool Withdraw(float Amount)
    {
        if (Amount > _AccountBalance)
            return false;
        else
        {
            _AccountBalance -= Amount;
            Save();
            return true;
        }
    }

    bool Transfer(float Amount, clsBankClient &DestinationClient)
    {
        if (Amount > _AccountBalance)
        {
            return false;
        }

        Withdraw(Amount);
        DestinationClient.Deposit(Amount);
        _RegisterTransferLog(Amount, DestinationClient);

        return true;
    }

    static vector<stTransferLogRecord> GetTransferLogList()
    {
        fstream myFile;
        myFile.open("TransferLog.txt", ios::in);
        vector<stTransferLogRecord> vTransferLogRecord;

        if (myFile.is_open())
        {
            string Line;
            stTransferLogRecord TransferLogRecord;
            while (getline(myFile, Line))
            {
                TransferLogRecord = _ConvertTransferLogLineToRecord(Line);
                vTransferLogRecord.push_back(TransferLogRecord);
            }
            myFile.close();
        }

        return vTransferLogRecord;
    }
};
