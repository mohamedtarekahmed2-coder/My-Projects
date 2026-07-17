#include <iostream>
#include <vector>
#include "clsInputValidate.h"
using namespace std;

int main()
{
    // int x = clsInputValidate::ReadNumber<int>("Invalid Number inter again : ");
    // cout << x << '\n';
    // int y = clsInputValidate::ReadNumberBetween<int>(1, 5, "Invalid Number inter again : ");
    vector<int> s = clsInputValidate::ReadVector<int>(3, "kkk");
    return 0;
}