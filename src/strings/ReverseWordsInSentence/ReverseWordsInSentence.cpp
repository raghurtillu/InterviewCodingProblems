#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

void ReverseWordsInSentence(string& sentence)
{
    if (sentence.empty()) 
    {
        return;
    }

    reverse(sentence.begin(), sentence.end());
    size_t wStart = 0, wEnd = 0;
    size_t len = sentence.size();
    
    for (wEnd = 0; wEnd < len; ++wEnd) 
    {
        if (sentence[wEnd] != ' ') 
        {
            wStart = wEnd;
            while (wEnd < len && sentence[wEnd] != ' ') 
            {
                ++wEnd;
            }
            reverse(sentence.begin() + wStart, sentence.begin() + wEnd);
        }
    }
}
// Driver program to test above functions
int main()
{
    string values[] = { "a ",
                        "a b ",
                        "aba bab c",
                        "This is Phoenix string",
    };
    for (auto sentence : values) 
    {
        cout << sentence << endl;
        ReverseWordsInSentence(sentence);
        cout << sentence << endl;
    }
    return 0;
}
