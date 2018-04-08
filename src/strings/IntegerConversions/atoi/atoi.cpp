#include <iostream>
#include <vector>
#include <string>
using namespace std;

int atoi(const string& str)
{
    if (str.empty())
    {
        return 0;
    }
    bool sign = false; // true means negative
    bool numStart = false;
    int num = 0;

    for (auto c : str)
    {
        if (c == '+' || c == '-')
        {
            if (numStart == false)
            {
                sign = (c == '-') ? true : false;
            }
            else if (numStart == true)
            {
                break;
            }
        }
        else if (c >= '0' && c <= '9')
        {
            if (!numStart)
            {
                numStart = true;
            }
            if (numStart)
            {
                num *= 10;
                num += c - '0';
            }
        }
        else
        {
            if (numStart)
            {
                break;
            }
        }
    }
    if (sign)
    {
        num *= -1;
    }
    return num;
}

int main()
{
    const vector<string> inputs = {
        "42",
        "-3924x8fc",
        "abc-843t",
        "+1",
        "c++",
        "++1",
        "--4-5",
        "+-- +-6.3",
        "",
        " ",
        "-",
        "a8.3",
    };

    for (const auto& str : inputs)
    {
        cout << str << ": ";
        cout << atoi(str) << endl;
    }
    return 0;
}