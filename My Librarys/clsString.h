#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cctype>

using namespace std;

class clsString
{
public:
    //----------------------------------------------------------
    // Enums
    //----------------------------------------------------------
    enum enWhatToCount
    {
        SmallLetters,
        CapitalLetters,
        All
    };

private:
    string _value;

public:
    //----------------------------------------------------------
    // Constructors & Getters/Setters
    //----------------------------------------------------------
    clsString()
    {
        _value = "";
    }
    
    clsString(const string &str) : _value(str) {}

    void SetValue(const string &str)
    {
        _value = str;
    }

    string GetValue() const
    {
        return _value;
    }

    //----------------------------------------------------------
    // 1. Length & Word Count Methods
    //----------------------------------------------------------
    static int Length(const string &str)
    {
        return str.size();
    }

    int Length() const
    {
        return Length(_value);
    }

    static int CountWords(const string &str)
    {
        stringstream ss(str);
        string word;
        int count = 0;

        while (ss >> word)
            count++;

        return count;
    }

    int CountWords() const
    {
        return CountWords(_value);
    }

    //----------------------------------------------------------
    // 2. Case Manipulation Methods
    //----------------------------------------------------------
    static string UpperFirstLetterOfEachWord(string str)
    {
        for (size_t i = 0; i < str.size(); i++)
        {
            if (str[i] == ' ' && i != str.size() - 1)
            {
                str[i + 1] = toupper(str[i + 1]);
            }
            else if (i == 0)
            {
                str[i] = toupper(str[i]);
            }
        }
        return str;
    }

    void UpperFirstLetterOfEachWord()
    {
        _value = UpperFirstLetterOfEachWord(_value);
    }

    static string LowerFirstLetterOfEachWord(string str)
    {
        for (size_t i = 0; i < str.size(); i++)
        {
            if (str[i] == ' ' && i != str.size() - 1)
            {
                str[i + 1] = tolower(str[i + 1]);
            }
            else if (i == 0)
            {
                str[i] = tolower(str[i]);
            }
        }
        return str;
    }

    void LowerFirstLetterOfEachWord()
    {
        _value = LowerFirstLetterOfEachWord(_value);
    }

    static string ToUpper(string str)
    {
        for (char &ch : str)
        {
            ch = toupper(ch);
        }
        return str;
    }

    void ToUpper()
    {
        _value = ToUpper(_value);
    }

    static string ToLower(string str)
    {
        for (char &ch : str)
        {
            ch = tolower(ch);
        }
        return str;
    }

    void ToLower()
    {
        _value = ToLower(_value);
    }

    static char InvertLetterCase(char ch)
    {
        return isupper(ch) ? tolower(ch) : toupper(ch);
    }

    static string SwapCase(string str)
    {
        for (char &ch : str)
        {
            ch = InvertLetterCase(ch);
        }
        return str;
    }

    void SwapCase()
    {
        _value = SwapCase(_value);
    }

    //----------------------------------------------------------
    // 3. Letter & Character Counting Methods
    //----------------------------------------------------------
    static int CountLetters(const string &str, enWhatToCount whatToCount = enWhatToCount::All)
    {
        if (whatToCount == enWhatToCount::All)
            return str.length();

        int counter = 0;
        for (char ch : str)
        {
            if (whatToCount == enWhatToCount::CapitalLetters && isupper(ch))
                counter++;

            if (whatToCount == enWhatToCount::SmallLetters && islower(ch))
                counter++;
        }
        return counter;
    }

    int CountCapitalLetters() const
    {
        return CountLetters(_value, enWhatToCount::CapitalLetters);
    }

    int CountSmallLetters() const
    {
        return CountLetters(_value, enWhatToCount::SmallLetters);
    }

    static int CountSpecificLetter(const string &str, char letter, bool matchCase = true)
    {
        int counter = 0;
        for (char ch : str)
        {
            if (matchCase)
            {
                if (ch == letter)
                    counter++;
            }
            else
            {
                if (tolower(ch) == tolower(letter))
                    counter++;
            }
        }
        return counter;
    }

    int CountSpecificLetter(char letter, bool matchCase = true) const
    {
        return CountSpecificLetter(_value, letter, matchCase);
    }

    //----------------------------------------------------------
    // 4. Vowels Methods
    //----------------------------------------------------------
    static bool IsVowel(char ch)
    {
        ch = tolower(ch);
        return (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u');
    }

    static int CountVowels(const string &str)
    {
        int counter = 0;
        for (char ch : str)
        {
            if (IsVowel(ch))
                counter++;
        }
        return counter;
    }

    int CountVowels() const
    {
        return CountVowels(_value);
    }

    //----------------------------------------------------------
    // 5. Splitting, Trimming & Joining Methods
    //----------------------------------------------------------
    static vector<string> Split(string str, const string &delim)
    {
        vector<string> vString;
        size_t pos = 0;
        string sWord;

        while ((pos = str.find(delim)) != string::npos)
        {
            sWord = str.substr(0, pos);
            if (!sWord.empty())
            {
                vString.push_back(sWord);
            }
            str.erase(0, pos + delim.length());
        }

        if (!str.empty())
        {
            vString.push_back(str);
        }

        return vString;
    }

    vector<string> Split(const string &delim) const
    {
        return Split(_value, delim);
    }

    static string TrimLeft(const string &str, char ch = ' ')
    {
        size_t start = str.find_first_not_of(ch);
        return (start == string::npos) ? "" : str.substr(start);
    }

    void TrimLeft(char ch = ' ')
    {
        _value = TrimLeft(_value, ch);
    }

    static string TrimRight(const string &str, char ch = ' ')
    {
        size_t end = str.find_last_not_of(ch);
        return (end == string::npos) ? "" : str.substr(0, end + 1);
    }

    void TrimRight(char ch = ' ')
    {
        _value = TrimRight(_value, ch);
    }

    static string Trim(const string &str, char ch = ' ')
    {
        return TrimLeft(TrimRight(str, ch), ch);
    }

    void Trim(char ch = ' ')
    {
        _value = Trim(_value, ch);
    }

    static string TrimAll(const string &str, char ch = ' ')
    {
        string result = "";
        for (char c : str)
        {
            if (c != ch)
                result += c;
        }
        return result;
    }

    void TrimAll(char ch = ' ')
    {
        _value = TrimAll(_value, ch);
    }

    static string JoinString(const vector<string> &vString, const string &delim)
    {
        string result = "";
        for (size_t i = 0; i < vString.size(); i++)
        {
            result += vString[i];
            if (i < vString.size() - 1)
                result += delim;
        }
        return result;
    }

    static string JoinString(const string arrString[], int length, const string &delim)
    {
        string result = "";
        for (int i = 0; i < length; i++)
        {
            result += arrString[i];
            if (i < length - 1)
                result += delim;
        }
        return result;
    }

    string JoinElements(const string &sep = ", ") const
    {
        string result = "";
        for (size_t i = 0; i < _value.size(); i++)
        {
            result += _value[i];
            if (i < _value.size() - 1)
                result += sep;
        }
        return result;
    }

    //----------------------------------------------------------
    // 6. Manipulations & Modification Methods
    //----------------------------------------------------------
    static string ReverseWordsInString(const string &str)
    {
        vector<string> vString = Split(str, " ");
        string result = "";

        for (int i = (int)vString.size() - 1; i >= 0; i--)
        {
            result += vString[i];
            if (i > 0)
                result += " ";
        }
        return result;
    }

    void ReverseWordsInString()
    {
        _value = ReverseWordsInString(_value);
    }

    static string Reverse(string str)
    {
        int size = static_cast<int>(str.size());
        for (int i = 0; i < size / 2; i++)
        {
            swap(str[i], str[size - 1 - i]);
        }
        return str;
    }

    void Reverse()
    {
        _value = Reverse(_value);
    }

    static string ReplaceWord(const string &str, const string &stringToReplace, const string &strReplace, bool matchCase = true)
    {
        vector<string> vString = Split(str, " ");

        for (string &s : vString)
        {
            if (matchCase)
            {
                if (s == stringToReplace)
                    s = strReplace;
            }
            else
            {
                if (ToLower(s) == ToLower(stringToReplace))
                    s = strReplace;
            }
        }
        return JoinString(vString, " ");
    }

    string ReplaceWord(const string &stringToReplace, const string &strReplace, bool matchCase = true)
    {
        return ReplaceWord(_value, stringToReplace, strReplace, matchCase);
    }

    static string RemovePunctuations(const string &str)
    {
        string result = "";
        for (char ch : str)
        {
            if (!ispunct(ch))
            {
                result += ch;
            }
        }
        return result;
    }

    void RemovePunctuations()
    {
        _value = RemovePunctuations(_value);
    }

    static string Clean(const string &str, bool keepNums = true)
    {
        string result = "";
        result.reserve(str.size());

        for (char ch : str)
        {
            if (isalpha(ch) || ch == '_' || (keepNums && isdigit(ch)))
            {
                result += ch;
            }
        }
        return result;
    }

    string Clean(bool keepNums = true) const
    {
        return Clean(_value, keepNums);
    }

    static string SubString(const string &str, int start, int end, bool incEnd = true, bool countSpace = true)
    {
        string result = "";
        int limit = end;
        for (int i = start; (incEnd) ? i <= limit : i < limit; i++)
        {
            if (i >= (int)str.size())
                break;

            if (str.at(i) == ' ' && !countSpace)
                limit++;

            result += str.at(i);
        }
        return result;
    }

    string SubString(int start, int end, bool incEnd = true, bool countSpace = true) const
    {
        return SubString(_value, start, end, incEnd, countSpace);
    }

    static string ParseStr(const string &str)
    {
        string result = "";
        result.reserve(str.size());

        for (char ch : str)
        {
            if (ch == '=')
                result += ": ";
            else if (ch == '&')
                result += '\n';
            else
                result += ch;
        }
        return result;
    }

    string ParseStr() const
    {
        return ParseStr(_value);
    }

    static int ParseInt(const string &str)
    {
        int result = 0;
        int mult = 1;
        for (int i = (int)str.size() - 1; i >= 0; i--)
        {
            if ('0' <= str.at(i) && str.at(i) <= '9')
            {
                result += (str.at(i) - '0') * mult;
                mult *= 10;
            }
        }
        return result;
    }

    int ParseInt() const
    {
        return ParseInt(_value);
    }

    static string Repeat(const string &str, size_t repeatCount, char sep, bool showEndSep)
    {
        if (repeatCount == 0)
            return "";

        string result;
        result.reserve((str.size() + 1) * repeatCount);

        for (size_t i = 0; i < repeatCount; ++i)
        {
            result += str;
            if (i < repeatCount - 1 || showEndSep)
                result += sep;
        }
        return result;
    }

    string Repeat(size_t repeatCount, char sep, bool showEndSep) const
    {
        return Repeat(_value, repeatCount, sep, showEndSep);
    }

    static string Slice(const string &str, int start, int end, int step = 1, bool rev = false)
    {
        string result = "";
        for (int i = start; i <= end; i += step)
        {
            if (i >= (int)str.size())
                break;

            if (rev)
                result = str.at(i) + result;
            else
                result += str.at(i);
        }
        return result;
    }

    string Slice(int start, int end, int step = 1, bool rev = false) const
    {
        return Slice(_value, start, end, step, rev);
    }

    static string ZFill(const string &str, int width, char fill = '0')
    {
        int widthFill = width - static_cast<int>(str.size());
        string result = str;
        for (int i = 0; i < widthFill; i++)
        {
            result = fill + result;
        }
        return result;
    }

    void ZFill(int width, char fill = '0')
    {
        _value = ZFill(_value, width, fill);
    }

    //----------------------------------------------------------
    // 7. Boolean / Checkers Methods
    //----------------------------------------------------------
    static bool IsFirstCapital(const string &str)
    {
        for (size_t i = 0; i < str.size(); i++)
        {
            if ((i == 0 || isspace(str[i - 1])) && !isupper(str[i]))
                return false;
        }
        return true;
    }

    bool IsFirstCapital() const
    {
        return IsFirstCapital(_value);
    }

    static bool StartsWith(const string &str, const string &prefix, bool sensitive = true)
    {
        if (str.size() < prefix.size())
            return false;

        for (size_t i = 0; i < prefix.size(); i++)
        {
            if (sensitive)
            {
                if (str[i] != prefix[i])
                    return false;
            }
            else
            {
                if (tolower(str[i]) != tolower(prefix[i]))
                    return false;
            }
        }
        return true;
    }

    bool StartsWith(const string &prefix, bool sensitive = true) const
    {
        return StartsWith(_value, prefix, sensitive);
    }

    static bool IsNaN(const string &str)
    {
        for (char c : str)
        {
            if (c < '0' || '9' < c)
                return true;
        }
        return false;
    }

    bool IsNaN() const
    {
        return IsNaN(_value);
    }

    //----------------------------------------------------------
    // 8. Helper & Utility Methods (Vectors, Formatting, etc.)
    //----------------------------------------------------------
    static vector<string> FillVector(const string &str, int num)
    {
        return vector<string>(num, str);
    }

    vector<string> FillVector(int num) const
    {
        return FillVector(_value, num);
    }

    static string MoneyFormat(int num)
    {
        string snum = to_string(num);
        string result = "";
        int count = 0;
        for (int i = (int)snum.size() - 1; i >= 0; i--)
        {
            result = snum[i] + result;
            count++;
            if (count % 3 == 0 && i != 0)
                result = "," + result;
        }
        return result;
    }

    static int Ord(const string &str, int index = 0)
    {
        return str.at(index);
    }

    int Ord(int index = 0) const
    {
        return Ord(_value, index);
    }

    static char Chr(int num)
    {
        return static_cast<char>(num);
    }

    static vector<string> PushItem(vector<string> vec, const string &item)
    {
        vec.push_back(item);
        return vec;
    }
};
