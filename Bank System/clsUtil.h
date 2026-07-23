#pragma once

#include <iostream>
#include <string>
#include <ctime>
#include "clsDate.h"

using namespace std;
class clsUtil
{
private:
public:
    enum enCharType
    {
        SmallLetter = 1,
        CapitalLetter = 2,
        Digit = 3,
        MixChars = 4,
        SpecialCharacter = 5
    };

    static void Srand()
    {
        // Seeds the random number generator in C++, called only once
        srand((unsigned)time(NULL));
    }

    static int RandomNumber(int From, int To)
    {
        // Function to generate a random number
        int randNum = rand() % (To - From + 1) + From;
        return randNum;
    }

    static char GetRandomCharacter(enCharType CharType)
    {
        // updated this method to accept mix chars
        if (CharType == MixChars)
        {
            // Capital/Small/Digits only
            CharType = (enCharType)RandomNumber(1, 3);
        }

        switch (CharType)
        {
        case enCharType::SmallLetter:
        {
            return char(RandomNumber(97, 122));
            break;
        }
        case enCharType::CapitalLetter:
        {
            return char(RandomNumber(65, 90));
            break;
        }
        case enCharType::SpecialCharacter:
        {
            return char(RandomNumber(33, 47));
            break;
        }
        case enCharType::Digit:
        {
            return char(RandomNumber(48, 57));
            break;
        }
        default:
        {
            return char(RandomNumber(65, 90));
            break;
        }
        }
    }

    static string GenerateWord(enCharType CharType, short Length)
    {
        string Word;
        for (int i = 1; i <= Length; i++)
            Word = Word + GetRandomCharacter(CharType);

        return Word;
    }

    static string GenerateKey(enCharType CharType = CapitalLetter)
    {
        string Key = "";

        Key = GenerateWord(CharType, 4) + "-";
        Key = Key + GenerateWord(CharType, 4) + "-";
        Key = Key + GenerateWord(CharType, 4) + "-";
        Key = Key + GenerateWord(CharType, 4);

        return Key;
    }

    static void GenerateKeys(short NumberOfKeys, enCharType CharType)
    {
        for (int i = 1; i <= NumberOfKeys; i++)
        {
            cout << "Key [" << i << "] : ";
            cout << GenerateKey(CharType) << endl;
        }
    }

    static void FillArrayWithRandomNumbers(int arr[100], int arrLength, int From, int To)
    {
        for (int i = 0; i < arrLength; i++)
            arr[i] = RandomNumber(From, To);
    }

    static void FillArrayWithRandomWords(string arr[100], int arrLength, enCharType CharType, short Wordlength)
    {
        for (int i = 0; i < arrLength; i++)
            arr[i] = GenerateWord(CharType, Wordlength);
    }

    static void FillArrayWithRandomKeys(string arr[100], int arrLength, enCharType CharType)
    {
        for (int i = 0; i < arrLength; i++)
            arr[i] = GenerateKey(CharType);
    }

    template <typename ty>
    static void Swap(ty &A, ty &B)
    {
        ty Temp;

        Temp = A;
        A = B;
        B = Temp;
    }

    static void Swap(clsDate &A, clsDate &B)
    {
        clsDate::SwapDates(A, B);
    }

    static void ShuffleArray(int arr[100], int arrLength)
    {
        for (int i = 0; i < arrLength; i++)
            Swap(arr[RandomNumber(1, arrLength) - 1], arr[RandomNumber(1, arrLength) - 1]);
    }

    static void ShuffleArray(string arr[100], int arrLength)
    {
        for (int i = 0; i < arrLength; i++)
            Swap(arr[RandomNumber(1, arrLength) - 1], arr[RandomNumber(1, arrLength) - 1]);
    }

    static string Tabs(short NumberOfTabs)
    {
        string t = "";

        for (int i = 1; i < NumberOfTabs; i++)
        {
            t = t + "\t";
            cout << t;
        }
        return t;
    }

    static string EncryptText(string Text, short EncryptionKey)
    {
        for (int i = 0; i <= Text.length(); i++)
            Text[i] = char((int)Text[i] + EncryptionKey);

        return Text;
    }

    static string DecryptText(string Text, short EncryptionKey)
    {
        for (int i = 0; i <= Text.length(); i++)
            Text[i] = char((int)Text[i] - EncryptionKey);

        return Text;
    }

    static string NumberToText(long long Number)
    {
        if (Number == 0)
            return "Zero";

        if (Number < 0)
            return "Negative " + NumberToText(-Number);

        string units[] = {"", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine",
                          "Ten", "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen",
                          "Seventeen", "Eighteen", "Nineteen"};

        string tens[] = {"", "", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"};

        if (Number < 20)
            return units[Number];
        if (Number < 100)
            return tens[Number / 10] + (Number % 10 ? " " + NumberToText(Number % 10) : "");
        if (Number < 1000)
            return units[Number / 100] + " Hundred" + (Number % 100 ? " " + NumberToText(Number % 100) : "");
        if (Number < 1000000)
            return NumberToText(Number / 1000) + " Thousand" + (Number % 1000 ? " " + NumberToText(Number % 1000) : "");
        if (Number < 1000000000)
            return NumberToText(Number / 1000000) + " Million" + (Number % 1000000 ? " " + NumberToText(Number % 1000000) : "");

        return NumberToText(Number / 1000000000) + " Billion" + (Number % 1000000000 ? " " + NumberToText(Number % 1000000000) : "");
    }
};
