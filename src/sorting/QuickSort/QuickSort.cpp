#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

size_t Partition(vector<int>& inputs, size_t low, size_t high)
{
    if (inputs.empty() || low > high || high - low > inputs.size())
    {
        return SIZE_MAX;
    }

    auto pivot = inputs[high];
    
    size_t i = low-1;
    for (size_t j = low; j < high; ++j)
    {
        if (inputs[j] <= pivot)
        {
            i++;
            swap(inputs[j], inputs[i]);
        }
    }
    swap(inputs[i+1], inputs[high]);
    return i + 1;
}

void QuickSort(vector<int>& inputs, size_t low, size_t high)
{
    if (inputs.size() <= 1 || low >= high || high - low > inputs.size())
    {
        return;
    }

    size_t pivotIndex = Partition(inputs, low, high);
    if (pivotIndex == SIZE_MAX)
    {
        // should not happen
        return;
    }

    QuickSort(inputs, low, pivotIndex - 1);
    QuickSort(inputs, pivotIndex + 1, high);
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
	QuickSort(inputs, 0, inputs.size()-1);
	PrintVector(inputs);

	return 0;
}
