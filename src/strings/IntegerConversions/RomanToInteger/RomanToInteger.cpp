#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

int RomanToInt(string s)
{
	if (s.empty())
	{
		return 0;
	}

	unordered_map<char, int> lookup = 
	{
		{ 'I' , 1 },
		{ 'V' , 5 },
		{ 'X' , 10 },
        { 'L' , 50 },
		{ 'C' , 100 },
		{ 'D' , 500 },
		{ 'M' , 1000 },
	};
	
	int sum = lookup[s.back()];
	for (size_t i = s.size() - 2; i != SIZE_MAX; --i)
	{
		if (lookup[s[i]] < lookup[s[i + 1]])
		{
			sum -= lookup[s[i]];
		}
		else
		{
			sum += lookup[s[i]];
		}
	}
	return sum;
}

// Driver code
int main()
{
	vector<string> inputs = 
	{
		"I",
		"XCIX",
		"CXLIII",
		"C",
		"MMCXLVIII",
		"MMCCXXII",
		"MMMCMLXXXIX",
	};

	cout << "Integers for the Roman numerals:" << endl;
	for (string s : inputs)
	{
		cout << s << ": " << RomanToInt(s) << endl;
	}

	return 0;
}
