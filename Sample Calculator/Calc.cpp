#include <iostream>
using namespace std;

class Calc
{
private:
    int result = 0;
    pair<string, int> last_operation = make_pair("Clear", 0);

public:
    void Add(int num)
    {
        result += num;
        last_operation = make_pair("Adding", num);
    }
    void Subtract(int num)
    {
        result -= num;
        last_operation = make_pair("Subtracting", num);
    }
    void Divide(int num)
    {
        if(num == 0) num = 1;
        result /= num;
        last_operation = make_pair("Dividing", num);
    }
    void Multiply(int num)
    {
        result *= num;
        last_operation = make_pair("Multiplying", num);
    }
    void Clear()
    {
        result = 0;
        last_operation = make_pair("Clear", 0);
    }
    void PrintResult()
    {
        cout << "Result After " << last_operation.first << " " <<last_operation.second;
        cout << " is : " << result << '\n';
    }
};


int main()
{
    Calc a;
    a.Clear();
    a.Add(10);
    a.PrintResult();
    a.Add(100);
    a.PrintResult();
    a.Subtract(20);
    a.PrintResult();
    a.Divide(0);
    a.PrintResult();
    a.Divide(2);
    a.PrintResult();
    a.Multiply(3);
    a.PrintResult();
    a.Clear();
    a.PrintResult();
    return 0;
}