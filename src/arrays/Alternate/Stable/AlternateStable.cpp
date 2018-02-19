#include <iostream>
#include <vector>
using namespace std;
 
// Utility function to right rotate all elements between [outOfPlace, cur]
void RightRotate(vector<int>& arr, int outOfPlace, int cur)
{
    if (arr.empty() || outOfPlace <= 0 || outOfPlace >= arr.size() || cur <= 0 || cur >= arr.size())
    {
        return;
    }

    auto c = arr[cur];
    for (int i = cur; i > outOfPlace; --i)
    {
        arr[i] = arr[i-1];
    }
    arr[outOfPlace] = c;
}
 
void AlternateStable(vector<int>& arr)
{
    int n = static_cast<int>(arr.size());
    int outOfPlace = -1;
 
    for (int index = 0; index < n; ++index)
    {
        if (outOfPlace >= 0)
        {
            // find the item which must be moved into the out-of-place
            // entry if out of place entry is positive and current
            // entry is negative OR if out-of-place entry is negative
            // and current entry is negative then right rotate
            //
            // [...-3, -4, -5, 6...] -->   [...6, -3, -4, -5...]
            //      ^                          ^
            //      |                          |
            //     outOfPlace      -->      outOfPlace
            //
            if ((arr[index] >= 0 && arr[outOfPlace] < 0) || (arr[index] < 0 && arr[outOfPlace] >= 0))
            {
                RightRotate(arr, outOfPlace, index);
 
                // the new out of place entry is now 2 steps ahead
                if (index - outOfPlace > 2)
                {
                    outOfPlace = outOfPlace + 2;
                }
                else
                {
                    outOfPlace = -1;
                }
            }
        }
 
 
        // if no entry has been flagged out of place
        if (outOfPlace == -1)
        {
            // check if current entry is out of place
            if ((arr[index] >= 0 && !(index & 1)) || (arr[index] < 0 && (index & 1)))
            {
                outOfPlace = index;
            }
        }
    }
}
 
// Driver program
int main()
{
    vector<vector<int>> inputs = 
    {
        {-5, 3, 4, 5, -6, -2, 8, 9, -1, -4},
        {-5, -2, 5, 2, 4, 7, 1, 8, 0, -8},
        {-5, 3, -4, -7, -1, -2 , -8, -9, 1 , -4},
    };

    for (auto& input : inputs)
    {
        cout << "For the inputs: ";
        for (auto i : input)
        {
            cout << i << " ";
        }
        cout << endl;

        AlternateStable(input);
        cout << "Alternate stable sequence is: ";
        for (auto i : input)
        {
            cout << i << " ";
        }
        cout << endl;
    }
    return 0;
}