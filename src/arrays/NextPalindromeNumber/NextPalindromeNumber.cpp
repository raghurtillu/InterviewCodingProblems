#include <iostream>
#include <vector>
#include <string>
using namespace std;

void _NextPalindromeNumber(vector<int>& a)
{
    if (a.empty())
    {
        return;
    }
    
    int n = static_cast<int>(a.size());
    int mid = n / 2;
    int i = mid - 1;
    int j = mid;
    if (n & 1)
    {
        j = mid + 1;
    }

    while (i >= 0)
    {
        if (a[i] != a[j])
        {
            break;
        }
        i--;
        j++;
    }

    bool leftSmaller = false;
    if (i < 0 || a[i] < a[j])
    {
        leftSmaller = true;
    }

    while (i >= 0)
    {
        a[j++] = a[i--];
    }

    if (leftSmaller == true)
    {
        int carry = 1;
        i = mid - 1;
        j = mid;

        if (n & 1)
        {
            a[mid] += carry;
            carry = a[mid] / 10;
            a[mid] %= 10;
            j = mid + 1;
        }

        while (i >= 0)
        {
            a[i] += carry;
            carry = a[i] / 10;
            a[i] %= 10;
            a[j++] = a[i--];
        }
    }
}

int NextPalindromeNumber(int num)
{
    vector<int> a;

    bool all9s = true;
    int origNum = num;
    while (num > 0)
    {
        auto digit = num % 10;
        a.push_back(digit);
        num = num / 10;
        if (all9s && digit != 9)
        {
            all9s = false;
        }
    }

    if (all9s)
    {
        return origNum + 2;
    }

    reverse(a.begin(), a.end());
    _NextPalindromeNumber(a);

    int res = 0;
    for (size_t i = 0; i < a.size(); ++i)
    {
        res *= 10;
        res += a[i];
    }
    return res;
}

int main()
{
    vector<int> inputs = 
    {
        1234,
        1345,
        4312,
        9999,
    };

    for (auto i : inputs)
    {
        auto res = NextPalindromeNumber(i);
        cout << "Next palindrome number for " << i << " is " << res << endl;
    }
    return 0;
}