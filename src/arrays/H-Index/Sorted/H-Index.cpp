#include <iostream>
#include <vector>
using namespace std;
// https://leetcode.com/problems/h-index-ii/description/
// Input: citations = [0,1,3,5,6]
// Output: 3 
// Explanation: [0,1,3,5,6] means the researcher has 5 papers in total and each of them had 
// received 0, 1, 3, 5, 6 citations respectively. 
// Since the researcher has 3 papers with at least 3 citations each and the remaining 
// two with no more than 3 citations each, her h-index is 3
//
size_t HIndex(const vector<int>& citations)
{
    // search for the highest index which matches the condition citations[index] >= length(citations) - index
    size_t n = citations.size();
    size_t low = 0, high = n - 1;
    while (true)
    {
        if (low > high)
        {
            break;
        }
        auto mid = (low + high) >> 1;
        if (citations[mid] == n - mid)
        {
            return n - mid;
        }
        else if (citations[mid] < n - mid)
        {
            low = n - mid;
        }
        else if (citations[mid] > n - mid)
        {
            high = mid - 1;
        }
    }
    return n - low;
}
int main()
{
    vector<vector<int>> values = 
    {
        {2, 3, 4, 5, 6, 7},
        {0, 1, 3, 5, 6},
    };

    for (const auto& inputs : values)
    {
        cout << "For the inputs: ";
        for (auto i : inputs)
        {
            cout << i << " ";
        }
        cout << endl;
        auto val = HIndex(inputs);
        cout << "there are " << val << " elements which are greater than or equal to " << val << endl;
    }

    return 0;
}
