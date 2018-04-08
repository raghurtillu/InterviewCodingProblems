#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Given an integer in the range 1-3999, convert it to a roman numeral

string IntegerToRoman(int num)
{
    string table[4][10] = 
    {
        {"", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"},
        {"", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"},
        {"", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM"},
        {"", "M", "MM", "MMM"},
    };

    string result;
    size_t unitsIndex = 0;
    while (num > 0)
    {
        int temp = num % 10;
        result = table[unitsIndex][temp] + result;
        num /= 10;
        ++unitsIndex;
    }
    return result;
}
int main()
{
    vector<int> numbers = 
    {
        1,
        99,
        143,
        100,
        0,
        2148,
        2222,
        3989,
    };

    cout << "Roman numerals for the numbers:" << endl;
    for (auto num : numbers)
    {
        cout << num << ": " << IntegerToRoman(num) << endl;
    }
    return 0;
}