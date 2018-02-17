#include <iostream>
#include <vector>

using namespace std;

void Merge(vector<int>& inputs, size_t low, size_t high)
{
    size_t mid = low + ((high - low) >> 1);

    vector<int> left(inputs.begin() + low, inputs.begin() + mid + 1);
    vector<int> right(inputs.begin() + mid + 1, inputs.begin() + high + 1);
    
    size_t lSize = mid - low + 1;
    size_t rSize = high - mid;

    size_t i = 0, j = 0, k = low;
    while (i < lSize && j < rSize)
    {
        if (left[i] <= right[j])
        {
            inputs[k++] = left[i++];
        }
        else
        {
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
}

void MergeSort(vector<int>& inputs, size_t low, size_t high)
{
    if (inputs.size() <= 1 || low >= high || high - low > inputs.size())
    {
        return;
    }
    
    size_t mid = (low + high) >> 1;
    
    MergeSort(inputs, low, mid);
    MergeSort(inputs, mid+1, high);
    
    Merge(inputs, low, high);
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
    vector<int> inputs = {12, 11, 13, 5, 6, 7};
	
    cout << "Input before sorting: " << endl;
    PrintVector(inputs);
    	
    cout << "Input after sorting: " << endl;
    MergeSort(inputs, 0, inputs.size()-1);
    PrintVector(inputs);

    return 0;
}
