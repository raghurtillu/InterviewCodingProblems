#include <iostream>
#include <vector>
using namespace std;

// https://leetcode.com/problems/integer-to-english-words/description/
// Convert a non-negative integer to its english words representation
// Given input is guaranteed to be less than 231 - 1.
// Input: 123
// Output: "One Hundred Twenty Three"
// Input: 12345
// Output: "Twelve Thousand Three Hundred Forty Five"
// Input: 1234567
// Output: "One Million Two Hundred Thirty Four Thousand Five Hundred Sixty Seven"

static const string digits[20] = 
{
    "Zero", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", 
    "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen",
};
static const string tens[10] = 
{
    "Zero", "Ten", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety",
};

string _IntegerToEnglishWords(int num)
{
    if (num >= 1000000000)
    {
        return _IntegerToEnglishWords(num / 1000000000) + " Billion" + _IntegerToEnglishWords(num % 1000000000);
    }
    else if (num >= 1000000)
    {
        return _IntegerToEnglishWords(num / 1000000) + " Million" + _IntegerToEnglishWords(num % 1000000);
    }
    else if (num >= 1000)
    {
        return _IntegerToEnglishWords(num / 1000) + " Thousand" + _IntegerToEnglishWords(num % 1000);
    }
    else if (num >= 100)
    {
        return _IntegerToEnglishWords(num / 100) + " Hundred" + _IntegerToEnglishWords(num % 100);
    }
    else if (num >= 20)
    {
        return " " + tens[num / 10] + _IntegerToEnglishWords(num % 10);
    }
    else if (num >= 1)
    {
        return " " + digits[num];
    }
    // should never reach here
    return " ";
}

string IntegerToEnglishWords(int num)
{
    if (num == 0) { return "Zero"; }
    string res = _IntegerToEnglishWords(num);
    return res;
}

int main()
{
    vector<int> inputs =  
    {
        0,
        1,
        9,
        10,
        100,
        101,
        110,
        123,
        12345,
        1234567,
        1234567891,
    };
    cout << "Number to English words for the following inputs: " << endl;
    for (int num : inputs)
    {
        cout << num << ":" << IntegerToEnglishWords(num) << endl;
    }
    return 0;
}