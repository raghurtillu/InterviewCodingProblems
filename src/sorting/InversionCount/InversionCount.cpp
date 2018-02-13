#include <iostream>
#include <vector>

using namespace std;

size_t Merge(vector<int>& inputs, size_t low, size_t high)
{
    size_t mid = low + ((high - low) >> 1);

    vector<int> left(inputs.begin() + low, inputs.begin() + mid + 1);
    vector<int> right(inputs.begin() + mid + 1, inputs.begin() + high + 1);
    
    size_t lSize = mid - low + 1;
    size_t rSize = high - mid;

    size_t inversionCount = 0;
    size_t i = 0, j = 0, k = low;
    while (i < lSize && j < rSize)
    {
        if (left[i] <= right[j])
        {
            inputs[k++] = left[i++];
        }
        else
        {
            // if inputs[i] is greater than inputs[j], then there are (mid – i) inversions. 
            // because left and right subarrays are sorted, so all the remaining elements in 
            // left-subarray (inputs[i+1], [i+2] … a[mid]) will be greater than inputs[j]
            inversionCount += lSize - i;
            inputs[k++] = right[j++];
        }
    }
    
    // copy left overs from either vectors
    while (i < lSize)
    {
        inputs[k++] = left[i++];
    }
    while (j < rSize)
    {
        inputs[k++] = right[j++];
    }
    return inversionCount;
}

size_t MergeSort(vector<int>& inputs, size_t low, size_t high)
{
    if (inputs.size() <= 1 || low >= high || high - low > inputs.size())
    {
        return 0;
    }
    
    size_t mid = (low + high) >> 1;
    
    size_t leftCount = MergeSort(inputs, low, mid);
    size_t rightCount = MergeSort(inputs, mid+1, high);
    
    return leftCount + rightCount + Merge(inputs, low, high);
}

void PrintVector(const vector<int>& inputs)
{
    for (auto i : inputs)
	{
	    cout << i << " ";
	}
	cout << endl;
}

int main()
{
	vector<vector<int>> values = 
    {
        {12, 11, 13, 5, 6, 7},
        {2, 7, 5, 3},
        {8, 1, 0, -1, 5},
        {4, 3, 2, 1},
    };

    for (auto inputs : values)
    {
        cout << "For the inputs: " << endl;
	    PrintVector(inputs);
	    cout << "inversion count is: " << MergeSort(inputs, 0, inputs.size()-1) << endl;
    }
	
	return 0;
}
