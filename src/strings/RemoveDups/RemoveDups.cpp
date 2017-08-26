#include <iostream>
#include <string>
using namespace std;

void removeDups(string& str)
{
    if (str.empty()) 
    {
        return;
    }
    size_t freq[256] = { 0 };
    size_t i = 0;
    for (size_t j = 0; j < str.size(); ++j) 
    {
        size_t index = str[j];
        freq[index]++;
        if (freq[index] == 1) 
        {
            if (i != j) 
            {
                str[i] = str[j];
            }
            i++;
        }
    }
    str = str.substr(0, i);
}

int main()
{
	string str = "a bb cc da";
    cout << "Original string: " << str << endl;
    removeDups(str);
	cout << "After removing dups: " << str << endl;
	return 0;
}
