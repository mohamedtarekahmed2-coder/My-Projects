#include <iostream>
#include "clsBackClient.h"

using namespace std;

int main()
{
    clsBackClient Client1 = clsBackClient::Find("A101");
    Client1.Print();
    Client1 = clsBackClient::Find("A101", "1939");
    Client1.Print();
    Client1 = clsBackClient::Find("A101", "12341111");
    Client1.Print();
    cout << clsBackClient::IsClientExist("A101");
    return 0;
}