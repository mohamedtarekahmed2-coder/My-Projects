#pragma once

#include <iostream>
#include <string>
#include <ctime>

using namespace std;
class clsUtil
{
private:
public:
    template <typename T>
    static void Swap(T &a, T &b)
    {
        T c = a;
        a = b;
        b = c;
    }

    static void Srand()
    {
        srand(time(0));
    }

    static int RandomNumber(int from, int to)
    {
        int randNum = rand() % (to - from + 1) + from;
        return randNum;
    }

    static void FillArrayWithRandomNumbers(int arr[], int arrLength, int From, int To)
    {
        for (int i = 0; i < arrLength; i++)
            arr[i] = RandomNumber(From, To);
    }

    static void ShuffleArray(int arr[], int arrLength)
    {

        for (int i = 0; i < arrLength; i++)
        {
            Swap(arr[RandomNumber(1, arrLength) - 1], arr[RandomNumber(1, arrLength) - 1]);
        }
    }

    static void ShuffleArray(string arr[], int arrLength)
    {

        for (int i = 0; i < arrLength; i++)
        {
            Swap(arr[RandomNumber(1, arrLength) - 1], arr[RandomNumber(1, arrLength) - 1]);
        }
    }

    static string Tabs(int count)
    {
        string t = "";
        for (int i = 0; i < count; i++)
        {
            t += "    ";
        }
        return t;
    }

    static string EncryptText(string Text, short EncryptionKey)
    {

        for (int i = 0; i <= Text.length(); i++)
        {

            Text[i] = char((int)Text[i] + EncryptionKey);
        }

        return Text;
    }

    static string DecryptText(string Text, short EncryptionKey)
    {

        for (int i = 0; i <= Text.length(); i++)
        {

            Text[i] = char((int)Text[i] - EncryptionKey);
        }
        return Text;
    }
};
