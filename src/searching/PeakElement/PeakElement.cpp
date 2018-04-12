#include <iostream>
#include <vector>
using namespace std;

// Find a Peak element
// A peak element is an element that is greater than its neighbors
// the array may contain multiple peaks, 
size_t _findPeakElement(const vector<int>& nums, size_t low, size_t high)
{
    if (low > high) { return SIZE_MAX; }
    else if (low == high) { return low; }
    else if (low == high - 1)  { return nums[low] > nums[high] ? low : high; }
    
    // 3 or more elements
    auto mid = (low + high) >> 1;
    if (mid - 1 >= low && mid + 1 <= high)
    {
        if (nums[mid] >= nums[mid - 1] && nums[mid] >= nums[mid + 1])
        {
            return mid;
        }
    }
    if (mid + 1 <= high)
    {
        if (nums[mid] < nums[mid + 1])
        {
            return _findPeakElement(nums, mid + 1, high);
        }
    }
    if (mid - 1 >= low)
    {
        if (nums[mid - 1] > nums[mid])
        {
            return _findPeakElement(nums, low, mid - 1);
        }
    }
    return mid;
}
size_t findPeakElement(const vector<int>& nums) 
{
    if (nums.empty()) { return INT_MIN; }
    return _findPeakElement(nums, 0, nums.size() - 1);
}

int main()
{
    const vector<vector<int>> inputs = 
    {
        {1, 2, 3, 1},
        {1, 3, 20, 4, 1, 0},
    };

    cout << "The index of peak element for the inputs: " << endl;
    for (const auto& input : inputs)
    {
        for (auto i : input)
        {
            cout << i << " ";
        }
        cout << ": ";
        size_t index = findPeakElement(input);
        if (index != SIZE_MAX)
        {
            cout << index << " (" << input[index] << ")" << endl;
        }
        else
        {
            cout << "Invalid" << endl;
        }
    }
    return 0;
}