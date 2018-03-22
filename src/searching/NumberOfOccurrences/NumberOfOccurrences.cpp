#include <iostream>
#include <vector>
using namespace std;

size_t FindFirstOccurrence(const vector<int>& a, size_t low, size_t high, int key)
{
    if (a.empty() || low > high || high - low > a.size() || low >= a.size())
    {
        return SIZE_MAX;
    }
    else if (low == high)
    {
        // only one element
        return a[low] == key ? low : SIZE_MAX;
    }

    // has 2 or more elements
    auto mid = low + ((high - low) >> 1);
    if (a[mid] == key)
    {
        if (mid - 1 >= low && a[mid - 1] == key)
        {
            // go left
            return FindFirstOccurrence(a, low, mid, key);
        }
        else
        {
            // mid is the first occurrence
            return mid;
        }
    }
    else
    {
        if (a[mid] > key)
        {
            return FindFirstOccurrence(a, low, mid, key);
        }
        else
        {
            return FindFirstOccurrence(a, mid + 1, high, key);
        }
    }
}

size_t FindLastOccurrence(const vector<int>& a, size_t low, size_t high, int key)
{
    if (a.empty() || low > high || high - low > a.size() || low >= a.size())
    {
        return SIZE_MAX;
    }
    else if (low == high)
    {
        // only one element
        return a[low] == key ? low : SIZE_MAX;                
    }
    
    // has 2 or more elements
    auto mid = low + ((high - low) >> 1);
    if (a[mid] == key)
    {
        if (mid + 1 <= high && a[mid+1] == key)
        {
            // go right
            return FindLastOccurrence(a, mid+1, high, key);
        }
        else
        {
            // mid is the last occurrence
            return mid;
        }
    }
    else
    {
        if (a[mid] > key)
        {
            return FindLastOccurrence(a, low, mid, key);
        }
        else
        {
            return FindLastOccurrence(a, mid + 1, high, key);
        }
    }
}

int main()
{
    vector<int> inputs = {1, 2, 2, 2, 2, 3, 4, 5, 5, 5, 7 ,8 ,8};
    vector<int> keys = {1, 2, 3, 4, 5, 7, 8, 10};

    cout << "For the inputs: " << endl;
    for (auto i : inputs)
    {
        cout << i << " ";
    }
    cout << endl;

    for (auto key : keys)
    {
        if (inputs.empty())
        {
            return 0;
        }

        size_t fIndex = FindFirstOccurrence(inputs, 0, inputs.size()-1, key);
        size_t lIndex = FindLastOccurrence(inputs, 0, inputs.size()-1, key);
        if (fIndex == SIZE_MAX || lIndex == SIZE_MAX || fIndex > lIndex)
        {
            cout << "The element " << key << " was not found in the array" << endl;
            continue;
        }
        size_t numOccurrences = lIndex - fIndex + 1;
        cout << "The number of occurrences of " << key << ": " << numOccurrences << 
        " (" << fIndex << ", " << lIndex << ")" << endl;
    }
    return 0;
}