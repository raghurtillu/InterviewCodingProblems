#include <iostream>
#include <vector>
using namespace std;

// Given an array of positive numbers and a number k, form maximum number from the input array
// of lengths [1, k] while maintaining relative order of the numbers in the array

// In the simple idea, we mentioned trying all possible length i. If we create max number for different i from scratch each time, that would be a waste of time. 
// Suppose num = [4, 9, 3, 2, 1, 8, 7, 6], we need to create max number with length from 1 to 8. For i==8, result is the original array. 
// For i==7, we need to drop 1 number from array, since 9 > 4, we drop 4, the result is [9, 3, 2, 1, 8, 7, 6]. For i==6, we need to drop 1 more number, 
// 3 < 9, skip, 2 < 3, skip, 1 < 2, skip, 8 > 1, we drop 1, the result is [9, 3, 2, 8, 7, 6]. For i==5, we need to drop 1 more, but this time, we needn't check from beginning, 
// during last scan, we already know [9, 3, 2] is monotonically non-increasing, so we check 8 directly, since 8 > 2, we drop 2, the result is [9, 3, 8, 7, 6]. 
// For i==4, we start with 8, 8 > 3, we drop 3, the result is [9, 8, 7, 6]. For i==3, we start with 8, 8 < 9, skip, 7 < 8, skip, 6 < 7, skip, by now, 
// we've got maximum number we can create from num without length constraint. 
// So from now on, we can drop a number from the end each time. 
// The result is [9, 8, 7], For i==2, we drop last number 7 and have [9, 8]. For i==1, we drop last number 8 and have [9].

void _GetMaxNumber(vector<int> nums, size_t k, vector<vector<int>>& results)
{
    if (results.size() != k) { return; }

    int i = 0, start = 0;
    while (!nums.empty())
    {
        if (nums.size() <= k)
        {
            results[nums.size() - 1] = nums;
        }
        bool erased = false;
        for (i = start; i < nums.size() - 1; ++i)
        {
            if (nums[i + 1] > nums[i])
            {
                nums.erase(nums.begin() + i);
                erased = true;
                break;
            }
        }
        if (!erased)
        {
            nums.pop_back();
        }
        start = (i == 0) ? 0 : i - 1;
    }
}

vector<int> GetMaxNumber(const vector<int>& inputs, size_t k)
{
    if (k == 0 || k > inputs.size())
    {
        return {};
    }

    vector<vector<int>> results(k);
    _GetMaxNumber(inputs, k, results);
    if (results.size() != k)
    {
        return {};
    }

    vector<int> ans(k, 0);
    for (size_t i = 0; i < results.size(); ++i)
    {
        int num = 0;
        for (size_t j = 0; j < results[i].size(); ++j)
        {
            num = num * 10 + results[i][j];
        }
        ans[i] = num;
    }
    reverse(ans.begin(), ans.end());
    return ans;
}

int main()
{
    vector<pair<vector<int>, size_t>> inputs = 
    {
        make_pair<vector<int>, size_t>({4, 3, 2, 1}, 3),
        make_pair<vector<int>, size_t>({1, 2, 3, 4}, 4),
        make_pair<vector<int>, size_t>({4, 9, 3, 2, 1, 6, 7, 8}, 2),
        make_pair<vector<int>, size_t>({4, 9, 3, 2, 1, 8, 7, 6}, 4),
        make_pair<vector<int>, size_t>({4, 5, 3, 2, 1, 6, 0, 8}, 5),
        make_pair<vector<int>, size_t>({4, 5, 3, 1, 2, 6, 0, 8}, 8),
    };

    for (size_t i = 0; i < inputs.size(); ++i)
    {
        const auto& p = inputs[i];
        if (i == 0 || inputs[i].first != inputs[i-1].first)
        {
            if (i != 0) { cout << endl; }
            cout << "For the inputs: ";
            cout << "{";
            for (size_t j = 0; j < p.first.size(); ++j)
            {
                cout << p.first[j];
                if (j != p.first.size() - 1)
                {
                    cout << ", ";
                }
            }
            cout << "}" << endl;
        }
        size_t k = p.second;
        vector<int> nums = GetMaxNumber(p.first, k);
        cout << "Maximum numbers in the digits range [1-" << k <<"] are:" << endl;
        for (auto num : nums)
        {
            cout << num << endl;
        }
    }
    return 0;
}