#include <iostream>
#include <iomanip>
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "clsUtil.h"

using namespace std;

void ReadClientInfo(clsBankClient &Client)
{
    cout << "Enter FirstName : ";
    Client.SetFirstName(clsInputValidate::Read<string>());

    cout << "Enter LastName : ";
    Client.SetLastName(clsInputValidate::Read<string>());

    cout << "Enter Email : ";
    Client.SetEmail(clsInputValidate::Read<string>());

    cout << "Enter Phone : ";
    Client.SetPhone(clsInputValidate::Read<string>());

    cout << "Enter PinCode : ";
    Client.SetPinCode(clsInputValidate::Read<string>());

    cout << "Enter Account Balance : ";
    Client.SetAccountBalance(clsInputValidate::Read<float>());

    system("cls");
}

void UpdateClient()
{
    cout << "\nPlease Enter Client Account Number : ";
    string AccountNumber = clsInputValidate::Read<string>();
    while (!clsBankClient::IsClientExist(AccountNumber))
    {
        cout << "\nAccount Number isn't fount, choose anther one : ";
        AccountNumber = clsInputValidate::Read<string>();
    }

    clsBankClient Client = clsBankClient::Find(AccountNumber);

    Client.Print();
    cout << "\n\nUpdate Client Info : ";
    cout << "\n_____________________\n";

    ReadClientInfo(Client);

    clsBankClient::enSaveResults SaveResult = Client.Save();

    switch (SaveResult)
    {
        case clsBankClient::enSaveResults::svSucceeded:
        {
            cout << "\nAccount Updated Successfully :-)\n";
            Client.Print();
            break;
        }
        case clsBankClient::enSaveResults::svFailEmptyObject:
        {
            cout << "\nError account was not saved because it's Empty";
            break;
        }
    }
}

void AddNewClient()
{
    cout << "\nPlease Enter Account Number : ";
    string AccountNumber = clsInputValidate::Read<string>();
    while (clsBankClient::IsClientExist(AccountNumber))
    {
        cout << "Account Number Is Already Used, Choose another one : ";
        AccountNumber = clsInputValidate::Read<string>();
    }

    clsBankClient NewClient = clsBankClient::GetAddNewClientObject(AccountNumber);
    ReadClientInfo(NewClient);

    clsBankClient::enSaveResults SaveResult = NewClient.Save();
    switch (SaveResult)
    {
    case clsBankClient::enSaveResults::svSucceeded:
        cout << "\nAccount Added Successfully \n";
        NewClient.Print();
        break;
    case clsBankClient::enSaveResults::svFailEmptyObject:
        cout << "\nError Account wasn't saved because it's Empty \n";
        break;
    case clsBankClient::enSaveResults::svFailAccountNumberExists:
        cout << "\nError Account wasn't saved because Account Number is Used\n";
        break;
    }
}

void DeleteClient()
{
    cout << "\nPlease Enter Account Number : ";
    string AccountNumber = clsInputValidate::Read<string>();
    while (!clsBankClient::IsClientExist(AccountNumber))
    {
        cout << "Account Number isn't found, Choose another one : ";
        AccountNumber = clsInputValidate::Read<string>();
    }

    clsBankClient Client = clsBankClient::Find(AccountNumber);
    Client.Print();
    
    cout << "\nAre you sure you want to delete this Client y/n? ";
    char Answer = 'n';
    cin >> Answer;
    if(Answer == 'y' || Answer == 'Y')
    {
        if(Client.Delete())
        {
            cout << "\nClient Deleted Successfully ";
            // Client.Print();
        }
        else
        {
            cout << "\nError Client wasn't Deleted\n";
        }
    }
}

void PrintClientRecordLine(clsBankClient Client)
{
    cout << "| " << left << setw(15) << Client.GetAccountNumber();
    cout << "| " << left << setw(20) << Client.FullName();
    cout << "| " << left << setw(12) << Client.GetPhone();
    cout << "| " << left << setw(30) << Client.GetEmail();
    cout << "| " << left << setw(10) << Client.GetPinCode();
    cout << "| " << left << setw(12) << Client.GetAccountBalance();
}

void ShowClientsList()
{
    vector<clsBankClient> vClient = clsBankClient::GetClientsList();

    cout << "\n\t\t\t\t\tClient List (" << vClient.size() << ") Client(s)";
    cout << "\n__________________________________________________________________________________________________________\n\n";
    cout << "| " << left << setw(15) << "Account Number";
    cout << "| " << left << setw(20) << "Client Name";
    cout << "| " << left << setw(12) << "Phone";
    cout << "| " << left << setw(30) << "Email";
    cout << "| " << left << setw(10) << "Pin Code";
    cout << "| " << left << setw(12) << "Balance";
    cout << "\n__________________________________________________________________________________________________________\n\n";
    if(vClient.size() == 0)
        cout << "No Data Exist";
    else 
    {
        for(clsBankClient &Client : vClient)
        {
            PrintClientRecordLine(Client);
            cout << '\n';
        }
    }
    cout << "\n__________________________________________________________________________________________________________\n\n";

}

void PrintClientRecordBalanceLine(clsBankClient Client)
{
    cout << "| " << left << setw(15) << Client.GetAccountNumber();
    cout << "| " << left << setw(40) << Client.FullName();
    cout << "| " << left << setw(12) << Client.GetAccountBalance();
}

void ShowTotalBalances()
{
    vector<clsBankClient> vClient = clsBankClient::GetClientsList();

    cout << "\n\t\t\t\t\tBalances List (" << vClient.size() << ") Client(s)";
    cout << "\n__________________________________________________________________________________________________________\n\n";
    cout << "| " << left << setw(15) << "Account Number";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Balance";
    cout << "\n__________________________________________________________________________________________________________\n\n";
    if(vClient.size() == 0)
        cout << "\t\t\t\t No Clients Available In ";
    else 
    {
        for(clsBankClient &Client : vClient)
        {
            PrintClientRecordBalanceLine(Client);
            cout << '\n';
        }
    }
    cout << "\n__________________________________________________________________________________________________________\n\n";

    double TotalBalances = clsBankClient::GetTotalBalances();
    cout << "Total Balances = " << fixed << setprecision(2) << TotalBalances << endl;
    cout << "( " << clsUtil::NumberToText(TotalBalances) << ")";
}


int main()
{
    ShowTotalBalances();
    return 0;
}