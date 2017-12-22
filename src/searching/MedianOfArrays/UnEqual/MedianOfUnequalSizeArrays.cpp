// a C++ program to find median of two sorted arrays of unequal sizes
#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

float medianSingle(const int arr[], int n)
{
	if (n <= 0)
	{
		return 0;
	}
	else if (n == 1)
	{
		return arr[0];
	}
	else if (n & 1)
	{
		return arr[n/2];
	}
	else
	{
		return (arr[n/2-1] + arr[n/2]) / 2;
	}
}

float medianOfTwo(int a, int b)
{
    return (a + b) / 2;
}

float medianOfThree(int a, int b, int c)
{
    return a + b + c - max(a, max(b, c)) - min(a, min(b, c));
}

float medianOfFour(int a, int b, int c, int d)
{
    return (a + b + c + d - max(a, max(b, max(c, d))) - min(a, min(b, min(c, d)))) / 2;
}

// This function assumes that n is smaller than or equal to m
float findMedianUtil(const int a[], int n, int b[], int m)
{
	// If smaller array is empty, return median from second array
	if (n == 0)
	{
		return medianSingle(b, m);
	}
	else if (n == 1)
	{
		// Case 1: If the larger array also has one element, simply call medianOfTwo
		if (m == 1)
		{
			return medianOfTwo(a[0], b[0]);
		}
			
		// Case 2: If the larger array has odd number of elements,
		// then consider the middle 3 elements of larger array and
		// the only element of smaller array. Take few examples
		// like following
		// a[] = {9}, b[] = {5, 8, 10, 20, 30}
		if (m & 1)
		{
			return medianOfTwo(b[m/2], medianOfThree(a[0], b[m/2 - 1], b[m/2 + 1]));
		}
		else
		{
			return medianOfThree(b[m/2], b[m/2-1], a[0]);
		}
	}
	else if (n == 2)
	{
		if (m == 2)
		{
			return medianOfFour(a[0], a[1], b[0], b[1]);
		}
		else if (m & 1)
		{
			return medianOfThree(b[m/2], max(a[0], b[m/2-1]), min(a[1], b[m/2+1]));
		}
		else
		{
			return medianOfFour(b[m/2], b[m/2-1], max(a[0], b[m/2-2]), min(a[1], b[m/2+1]));
		}
	}

	int idxA = (n - 1) / 2;
	int idxB = (m - 1) / 2;

	// if a[idxA] <= b[idxB] then median must exist in a[idxA....] and b[....idxB]
	if (a[idxA] <= b[idxB])
	{
		return findMedianUtil(a + idxA, n/2 + 1, b, m - idxA);
	}
	else
	{
		//if a[idxA] > b[idxB], then median must exist in a[...idxA] and b[idxB....]
		return findMedianUtil(a, n/2 + 1, b + idxA, m - idxA);
	}
}

// A wrapper function around findMedianUtil(). This function
// makes sure that smaller array is passed as first argument
// to findMedianUtil
float findMedian(int a[], int n, int b[], int m)
{
	if (n > m)
	{
		return findMedianUtil(b, m, a, n);
	}
	else
	{
		return findMedianUtil(a, n, b, m);
	}
}

int main()
{
	int a[] = {900};
	int b[] = {5, 8, 10, 20};

	int n = sizeof(a) / sizeof(a[0]);
	int m = sizeof(b) / sizeof(b[0]);

	cout << "For the inputs: {";
    for (auto i = 0; i < n; ++i)
    {
        cout << a[i];
        if (i != n - 1)
        {
            cout << ", ";
        }
    }
    cout << "} and {";
	
	for (auto i = 0; i < m; ++i)
    {
        cout << b[i];
        if (i != m - 1)
        {
            cout << ", ";
        }
    }
	cout << "}, the median is as follows" << endl;
	cout << fixed << setprecision(2) << findMedian(a, n, b, m) << endl;
	return 0;
}
