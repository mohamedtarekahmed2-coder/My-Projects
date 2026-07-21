#include <iostream>
#include "clsBackClient.h"
#include "clsInputValidate.h"

using namespace std;

void ReadClientInfo(clsBackClient &Client)
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
}

void UpdateClient()
{
    cout << "\nPlease Enter Client Account Number : ";
    string AccountNumber = clsInputValidate::Read<string>();
    while (!clsBackClient::IsClientExist(AccountNumber))
    {
        cout << "\nAccount Number isn't fount, choose anther one : ";
        AccountNumber = clsInputValidate::Read<string>();
    }

    clsBackClient Client = clsBackClient::Find(AccountNumber);

    Client.Print();
    cout << "\n\nUpdate Client Info : ";
    cout << "\n_____________________\n";

    ReadClientInfo(Client);

    clsBackClient::enSaveResults SaveResult = Client.Save();

    switch (SaveResult)
    {
        case clsBackClient::enSaveResults::svSucceeded:
        {
            cout << "\nAccount Updated Successfully :-)\n";
            Client.Print();
            break;
        }
        case clsBackClient::enSaveResults::svFailEmptyObject:
        {
            cout << "\nError account was not saved because it's Empty";
            break;
        }
    }
}

int main()
{
    UpdateClient();
    return 0;
}