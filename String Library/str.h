#pragma once

#include <iostream>
#include <vector>
using namespace std;

class clsString
{
private:
    string _val;

public:
    clsString()
    {
        _val = "";
    }
    clsString(const string &s) : _val(s) {};

    void set_str(const string &s)
    {
        _val = s;
    }

    string get_str()
    {
        return _val;
    }

    int count_words()
    {
        return count_words(_val);
    }

    static int count_words(const string &_val)
    {
        if (_val.size() == 0)
            return 0;

        char sep = ' ';
        int result = (_val.at(_val.size() - 1) == sep) ? 0 : 1;

        for (int i = 1; i < _val.size(); i++)
            if (_val[i] == sep && sep != _val[i - 1])
                result++;

        return result;
    }

    string clean(bool keepnums = true)
    {
        string result = "";
        result.reserve(_val.size());

        for (char ch : _val)
        {
            if (isalpha(ch) || ch == '_' || (keepnums && isdigit(ch)))
            {
                result += ch;
            }
        }
        return result;
    }

    string sub_string(int start, int end, bool inc_end = true, bool countspace = true)
    {
        string result = "";
        for (int i = start; (inc_end) ? i <= end : i < end; i++)
        {
            if (_val.at(i) == ' ' && !countspace)
                end++;
            result += _val.at(i);
        }
        return result;
    }

    string parse_str()
    {
        string result = "";
        result.reserve(_val.size());

        for (char ch : _val)
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

    int parse_int()
    {
        int result = 0,
            mult = 1;
        for (int i = _val.size() - 1; i >= 0; i--)
        {
            if ('0' <= _val.at(i) && _val.at(i) <= '9')
            {
                result += (_val.at(i) - '0') * mult;
                mult *= 10;
            }
        }
        return result;
    }

    string repeat(size_t repeat_count, char sep, bool showEndSep)
    {
        if (repeat_count == 0)
            return "";

        string result;
        result.reserve((_val.size() + 1) * repeat_count);

        for (size_t i = 0; i < repeat_count; ++i)
        {
            result += _val;

            if (i < repeat_count - 1 || showEndSep)
                result += sep;
        }
        return result;
    }

    void Reverse()
    {
        int size = static_cast<int>(_val.size());
        int up = size - 1;
        for (int i = 0; i < size / 2; i++)
            swap(_val.at(i), _val.at(up - i));
    }

    string Slice(int start, int end, int step = 1, bool rev = false)
    {
        string result = "";
        for (int i = start; i <= end; i += step)
            (rev) ? result = _val.at(i) + result : result += _val.at(i);
        return result;
    }

    void to_upper()
    {
        for (char &ch : _val)
        {
            if ('a' <= ch && ch <= 'z')
                ch -= 32;
        }
    }

    void to_lower()
    {
        for (char &ch : _val)
        {
            if ('A' <= ch && ch <= 'Z')
                ch += 32;
        }
    }

    void to_swap()
    {
        for (char &ch : _val)
        {
            if ('A' <= ch && ch <= 'Z')
                ch += 32;
            else if ('a' <= ch && ch <= 'z')
                ch -= 32;
        }
    }

    void zFill(int width, char fill = '0')
    {
        int width_fill = width - static_cast<int>(_val.size());
        for (int i = 0; i < width_fill; i++)
            _val = fill + _val;
    }

    bool is_first_capital()
    {
        for (int i = 0; i < _val.size(); i++)
        {
            if ((i == 0 || isspace(_val[i - 1])) && !isupper(_val[i]))
                return false;
        }
        return true;
    }

    string trim(const string &direction = "All", char ch = ' ')
    {
        string result = "";
        if (direction == "All")
        {
            for (int i = 0; i < _val.size(); i++)
                if (_val.at(i) != ch)
                    result += _val.at(i);
        }
        else if (direction == "Left")
        {
            bool take_it = false;
            for (int i = 0; i < _val.size(); i++)
            {
                if (_val.at(i) != ch || take_it)
                {
                    result += _val.at(i);
                    take_it = true;
                }
            }
        }
        else if (direction == "Right")
        {
            bool take_it = true;
            for (int i = 0; i < _val.size(); i++)
            {
                if (_val.at(i) == ch && take_it)
                {
                    result += _val.at(i);
                }
                else if (_val.at(i) != ch)
                {
                    result += _val.at(i);
                    take_it = false;
                }
            }
        }
        return result;
    }

    bool starts_with(const string &prefix, bool sensitive = true)
    {
        if (_val.size() < prefix.size())
            return false;

        for (int i = 0; i < prefix.size(); i++)
        {
            if ((sensitive) ? _val[i] != prefix[i] : (_val[i] != tolower(prefix[i])) && (_val[i] != toupper(prefix[i])))
                return false;
        }
        return true;
    }

    vector<string> fill_vector(int num)
    {
        vector<string> result(num);
        for (string &st : result)
            st = _val;
        return result;
    }

    bool isNaN()
    {
        for (char c : _val)
        {
            if (c < '0' || '9' < c)
            {
                return true;
            }
        }
        return false;
    }

    string join_elements(string sep = ", ")
    {
        string st;
        for (int i = 0; i < _val.size(); i++)
        {
            if (i == _val.size() - 1)
            {
                st += _val[i];
            }
            else
            {
                st += _val[i] + sep;
            }
        }
        return st;
    }

    static string money_format(int num)
    {
        string snum = to_string(num);
        string result = "";
        int count = 0;
        for (int i = snum.size() - 1; i >= 0; i--)
        {
            result = snum[i] + result;
            count++;
            if (count % 3 == 0 && i != 0)
                result = "," + result;
        }
        return result;
    }

    int ord(int num = 0)
    {
        return _val.at(num);
    }

    static char chr(int num)
    {
        return num;
    }

    static vector<string> push_item(const vector<string> &v, string item)
    {
        vector<string> st(v.size() + 1);
        for (int i = 0; i < st.size(); i++)
        {
            if (i != st.size() - 1)
                st[i] = v[i];
            else
                st[i] = item;
        }
        return st;
    }

};
