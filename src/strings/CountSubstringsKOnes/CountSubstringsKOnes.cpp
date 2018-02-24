#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Return the total number of substrings in a binary string containing k ones
// string s = “100101”
// K = 2
// prefix sum array = [1, 1, 1, 2, 2, 3]
//
// So, at index 3, we have prefix sum 2, 
// Now total indices from where sum is 2, is 1
// so result = 1
// Substring considered = [“1001”]
//
// At index 4, we have prefix sum 2,
// Now total indices from where sum is 2, is 
// 1 so result = 2
// Substring considered = [“1001”, “10010”]
//
// At index 5, we have prefix sum 3,
// Now total indices from where sum is 2, 
// is 3 so result = 5
// Substring considered = [“1001”, “10010”, “00101”, “0101”, “101”]
// so total is 1 + 1 + 3 = 5
//

size_t CountOfSubstringWithKOnes(const string& s, size_t k)
{
    if (s.empty() || k == 0 || k > s.size())
    {
        return 0;
    }

    size_t res = 0;
    size_t countOfOne = 0;
    vector<size_t> freq(s.size() + 1, 0);

    // initialize index having zero sum as 1
    freq[0] = 1;

    // loop over binary characters of string
    for (size_t i = 0; i < s.size(); ++i) 
    {
        // update countOfOne variable with value of ith character
        countOfOne += (s[i] - '0');

        // if value reaches more than k, then update result
        if (countOfOne >= k) 
        {
            // add frequency of indices, having sum (current sum - k), to the result
            res += freq[countOfOne - k];
        }
        // update freqency of one's count
        ++freq[countOfOne];
    }
    return res;
}

// Driver code to test above methods
int main()
{
    vector<pair<string, size_t>> inputs =
    {
        make_pair<string, size_t>("10010", 1),
        make_pair<string, size_t>("100101", 2),
    };

    for (const auto& p : inputs)
    {
        const string& s = p.first;
        size_t k = p.second;
        cout << "For the input: " << s << endl;
        cout << "The number of substrings containing " << k << " ones are ";
        cout << CountOfSubstringWithKOnes(s, k) << endl;
    }
    cout << endl;
    return 0;
}
