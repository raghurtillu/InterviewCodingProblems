#include <iostream>
#include <vector>
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

vector<string> splitText(const string& message, int charLimit)
{
    int charLimitNew = charLimit - 5;
    if (charLimitNew < 0)
    {
        return {message};
    }

    vector<string> result;
    vector<string> splitted = SplitString(message, " ");
    if (splitted.size() == 1)
    {
        // message has no word breaks; split the message at charLimit directly
        splitted.clear();
        int pos = 0;
        while (pos < message.size())
        {
            size_t len = min(static_cast<size_t>(charLimitNew), message.size() - pos);
            splitted.push_back(message.substr(pos, len));
            pos += len;
        }
    }
    
    string temp;

    for (int i = 0; i < splitted.size() - 1; ++i)
    {
        temp = splitted[i];
        // while length of temp and the next element combined is less than charLimit, 
        // temp = temp + next element
        while (temp.size() + 1 + splitted[i + 1].size() <= charLimitNew && 
            i + 1 < splitted.size() - 1)
        {
            temp = temp + " " + splitted[i + 1];
            ++i;
        }
        result.push_back(temp);
    }
    string lastElement = result[result.size() - 1];
    if (lastElement.size() + 1 + splitted[splitted.size() - 1].size() < charLimitNew)
    {
        result[result.size() - 1] = lastElement + " " + splitted[splitted.size() - 1];
    }
    else
    {
        result.push_back(splitted[splitted.size() - 1]);
    }
    int i = 1;
    for (auto& str : result)
    {
        str += "(" + to_string(i++) + "/" + to_string(result.size()) + ")";
    }
    return result;
}

int main() 
{
    vector<pair<string, int>> messagePair = 
    {
        // TODO: add more test cases
        {"Hello World", 6},
        {"IAmABiggerTextWithNoBreaks", 7},
        {"Hello Phoenix, your Uber is arriving now! and this is a bigger text", 7},
    };
    cout << "Message annotated chunks for the following message and character limits:" << endl;
    for (const auto& p : messagePair)
    {
        const string& message = p.first;
        int charLimit = p.second;
        cout << message << ", " << charLimit << endl;
        vector<string> result = splitText(message, charLimit);
        for (const auto& str : result)
        {
            cout << str << " ";
        }
        cout << endl;
    }
    return 0;
}