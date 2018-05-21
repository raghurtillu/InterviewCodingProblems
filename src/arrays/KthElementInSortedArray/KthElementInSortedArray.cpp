#include <iostream>
#include <vector>
#include <limits>
using namespace std;

// Input : Array 1 - 2 3 6 7 9
//         Array 2 - 1 4 8 10
//         k = 5
// Output : 6
// Explanation: The final sorted array would be -
// 1, 2, 3, 4, 6, 7, 8, 9, 10
// The 5th element of this array is 6.
// Input : Array 1 - 100 112 256 349 770
//         Array 2 - 72 86 113 119 265 445 892
//         k = 7
// Output : 256
// Explanation: Final sorted array is -
// 72, 86, 100, 112, 113, 119, 256, 265, 349, 445, 770, 892
// 7th element of this array is 256.

// int KthElementInSortedArray(int *arr1, int *end1, int *arr2, int *end2, int k)
// {
// 	if (arr1 == end1)
// 	{
// 		return arr2[k];
// 	}
// 	if (arr2 == end2)
// 	{
// 		return arr1[k];
// 	}

// 	int mid1 = (end1 - arr1) / 2;
// 	int mid2 = (end2 - arr2) / 2;

// 	if (mid1 + mid2 < k)
// 	{
// 		if (arr1[mid1] > arr2[mid2])
//         {
// 			//return KthElementInSortedArray(arr1, end1, arr2 + mid2 + 1, end2, k - mid2 - 1);
//             return KthElementInSortedArray(arr1, end1, arr2 + mid2 + 1, end2, k - mid2 - 1);
//         }
// 		else
//         {
// 			return KthElementInSortedArray(arr1 + mid1 + 1, end1, arr2, end2, k - mid1 - 1);
//         }
// 	}
// 	else
// 	{
// 		if (arr1[mid1] > arr2[mid2])
// 			return KthElementInSortedArray(arr1, arr1 + mid1, arr2, end2, k);
// 		else
// 			return KthElementInSortedArray(arr1, end1, arr2, arr2 + mid2, k);
// 	}
// }

int KthElementInSortedArray(int *arr1, int *end1, int *arr2, int *end2, int k)
{
	if (arr1 == end1)
	{
		return arr2[k];
	}
	if (arr2 == end2)
	{
		return arr1[k];
	}

	int mid1 = (end1 - arr1) / 2;
	int mid2 = (end2 - arr2) / 2;

    if (mid1 + mid2 < k)
    {
        if (arr1[mid1] > arr2[mid2])
        {
            return KthElementInSortedArray(arr1, end1, arr2 + mid2 + 1, end2, k - mid2 - 1);
        }
        else
        {
            return KthElementInSortedArray(arr1 + mid1 + 1, end1, arr2, end2, k - mid1 - 1);
        }
    }
    else // mid1 + mid2 > k
    {
        if (arr1[mid1] > arr2[mid2])
        {
            return KthElementInSortedArray(arr1, arr1 + mid1, arr2, end2, k);
        }
        else
        {
            return KthElementInSortedArray(arr1, end1, arr2, arr2 + mid2, k);
        }
    }
}

int main()
{
    vector<int> a = {2, 3, 6, 7, 9};
    vector<int> b = {1, 4, 8, 10};
    vector<int> pos = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    cout << "For the arrays: ";
    for (size_t i = 0; i < a.size(); ++i)
    {
        cout << a[i];
        if (i != a.size() - 1)
        {
            cout << ", ";
        }
    }
    cout << " and ";
    for (size_t i = 0; i < b.size(); ++i)
    {
        cout << b[i];
        if (i != b.size() - 1)
        {
            cout << ", ";
        }
    }
    cout << endl;
    for (auto k : pos)
    {
        int *arr1 = &a[0];
        int *end1 = &a[a.size()];
        int *arr2 = &b[0];
        int *end2 = &b[b.size()];

        int val = KthElementInSortedArray(arr1, end1, arr2, end2, k-1);
        cout << "Element at position " << k << " in sorted array is " << val << endl;
    }
    return 0;
}