#include <iostream>
#include <vector>
using namespace std;
 
// Utility function to right rotate all elements between [outofplace, cur]
void rightrotate(vector<int>& arr, int outofplace, int cur)
{
    auto c = arr[cur];
    for (int i = cur; i > outofplace; i--)
    {
        arr[i] = arr[i-1];
    }
    arr[outofplace] = c;
}
 
void rearrange(vector<int>& arr)
{
    int n = arr.size();
    int outofplace = -1;
 
    for (int index = 0; index < n; index ++)
    {
        if (outofplace >= 0)
        {
            // find the item which must be moved into the out-of-place
            // entry if out-of-place entry is positive and current
            // entry is negative OR if out-of-place entry is negative
            // and current entry is negative then right rotate
            //
            // [...-3, -4, -5, 6...] -->   [...6, -3, -4, -5...]
            //      ^                          ^
            //      |                          |
            //     outofplace      -->      outofplace
            //
            if (((arr[index] >= 0) && (arr[outofplace] < 0))
                || ((arr[index] < 0) && (arr[outofplace] >= 0)))
            {
                rightrotate(arr, outofplace, index);
 
                // the new out-of-place entry is now 2 steps ahead
                if (index - outofplace > 2)
                {
                    outofplace = outofplace + 2;
                }
                else
                {
                    outofplace = -1;
                }
            }
        }
 
 
        // if no entry has been flagged out-of-place
        if (outofplace == -1)
        {
            // check if current entry is out-of-place
            if (((arr[index] >= 0) && (!(index & 0x01)))
                || ((arr[index] < 0) && (index & 0x01)))
            {
                outofplace = index;
            }
        }
    }
}
 
// A utility function to print an array 'arr[]' of size 'n'
void printArray(const vector<int>& arr)
{
    for (auto c : arr)
    {
        cout << c << " ";
    }
    cout << endl;
}
 
// Driver program to test abive function
int main()
{
    //vector<int> arr = {1, 2, 3, -4, -1, 4};
    vector<vector<int>> inputs = {
        {-5, 3, 4, 5, -6, -2, 8, 9, -1, -4},
        {1, -7, 3, -4, -1, 4},
        {-5, -2, 5, 2, 4, 7, 1, 8, 0, -8},
        {-5, 3, -4, -7, -1, -2 , -8, -9, 1 , -4},
    };

    for (auto& val : inputs)
    {
        cout << "given array " << endl;
        printArray(val);

        rearrange(val);

        cout << "after rearranging " << endl;
        printArray(val);
    }
    return 0;
}