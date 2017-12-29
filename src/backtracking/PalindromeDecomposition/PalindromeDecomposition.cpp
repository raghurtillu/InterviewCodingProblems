// A simple program to find the largest subarray with equal number of 0s and 1s
#include <iostream>
#include <vector>
#include <string>
using namespace std;

bool isPalindrome(const string& s)
{
	if (s.empty())
	{
		return false;
	}

	size_t i = 0, j = s.size() - 1;
	while (i < j)
	{
		if (s[i++] != s[j--])
		{
			return false;
		}
	}
	return true;
}

void _palindromicDecomposition(const string& s, string& res, vector<string>& results)
{
	if (s.empty())
	{
		if (!res.empty())
		{
			results.push_back(res);
		}
		return;
	}

	// iterate over different prefixes of the string
	for (size_t i = 0; i < s.size(); ++i)
	{
		const string& prefix = s.substr(0, i + 1);
		if (isPalindrome(prefix))
		{
			res += prefix;
			res += "|";
			_palindromicDecomposition(s.substr(i + 1), res, results);
			res.pop_back();
			res.erase(res.end() - prefix.size(), res.end());
		}
	}
}

vector<string> palindromicDecomposition(const string& s)
{
	string res;
	vector<string> results;
	_palindromicDecomposition(s, res, results);
	return results;
}

int main()
{
	vector<string> inputs = 
	{
		"abracadabra",
		"desserts",
		"Neveroddoreven",
	};

	for (const string& input : inputs)
	{
		cout << "Palindromic decompositions for the input: " << input << " are as follows" << endl;
		vector<string>results = palindromicDecomposition(input);
		size_t i = 0;
		for (const auto& res : results)
		{
			cout << "[" << ++i << "] ";
			cout << res << endl;
		}
		cout << endl;
	}
	return 0;
}
