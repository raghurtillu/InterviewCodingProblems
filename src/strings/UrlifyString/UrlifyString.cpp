#include <iostream>
#include <string>
#include <vector>

using namespace std;

// urlify given string inplace
void UrlifyString(string& s)
{
    if (s.empty()) 
    {
        return;
    }
    
    // trim trailing spaces
    int i = s.size() - 1;
    while (i >= 0) 
    {
        if (s[i] != ' ') 
        {
            break;
        }
        i--;
    }
    s = s.substr(0, i+1);

    // count spaces in the string
    auto spaceCount = 0;
    for (auto c : s)
    {
        if (c == ' ')
        {
            spaceCount++;
        }
    }
    if (spaceCount == 0)
    {
        // nothing to do
        return;
    }

    // set an index to the end of the string prior to resizing
    i = s.size() - 1;

    // resize the string
    auto newSize = s.size() + (spaceCount << 1);
    s.resize(newSize);
    
    // set another index to the end of the resized string
    int j = s.size() - 1;

    while (j >= 0 && i >= 0)
    {
        if (s[i] == ' ')
        {
            // if space is encountered; encode 
            s[j--] = '0';
            s[j--] = '2';
            s[j--] = '%';
            i--;
        }
        else
        {
            if (i != j)
            {
                s[j] = s[i];
            }
            i--;
            j--;
        }
    }    
}

int main()
{
    vector<string> values = { "a b ",
        "    ",
        "  ab c",
        " nal  and a  ",
    };

    for (auto& word : values) 
    {
        cout << word << " after urlfying is ";
        UrlifyString(word);
        cout << word << endl;
    }
    
    return 0;
}