#include <iostream>
#include <vector>
#include <string>
using namespace std;

vector<string> SplitString(const string& str, const string& delimiter)
{
    if (str.empty() || delimiter.empty())
    {
        return vector<string>();
    }

    vector<string> res;
    size_t start = 0;
    size_t end = str.find(delimiter);

    while (end != string::npos)
    {
        res.push_back(str.substr(start, end - start));
        start = end + delimiter.size();
        end = str.find(delimiter, start);
    }
    res.push_back(str.substr(start, end));

    return res;
}

int main()
{
    
    vector<pair<string, string>> inputs = {
        make_pair<string, string>("scott>=tiger", ">="),
        make_pair<string, string>("scott>=tiger", "?"), // no delimiter, should return complete string
        make_pair<string, string>("scott>=tiger>=mushroom", ">="),
        make_pair<string, string>(">=>=", ">="),
    };

    for (const auto& p : inputs)
    {
        const string& str = p.first;
        const string& delimiter = p.second;

        cout << "For the string " << str << " and delimiter " << "\'" << delimiter << "\'" 
        << " the split strings are" << endl; 
        
        vector<string>res = SplitString(str, delimiter);
        for (const auto& word : res)
        {
            cout << word << " (" << word.size() << ")" << endl;
        }
        cout << endl;
    }
    return 0;
}