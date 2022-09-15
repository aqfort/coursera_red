#include <algorithm>
#include <string>
#include <vector>
#include <set>
#include <sstream>

#include "profile.h"
#include "test_runner.h"

using namespace std;

class Learner
{
private:
    set<string> dict;

public:
    int Learn(const vector<string> &words)
    {
        set<string> temp(words.begin(), words.end());

        int size = static_cast<int>(temp.size());

        dict.merge(temp);

        // cout << dict << endl << temp << endl;

        return size - static_cast<int>(temp.size());
    }

    vector<string> KnownWords()
    {
        return vector<string>{dict.begin(), dict.end()};
    }
};

int main()
{
    Learner learner;
    string line;

    int i = 0;

    while (getline(cin, line))
    {
        vector<string> words;
        stringstream ss(line);
        string word;

        while (ss >> word)
        {
            words.push_back(word);
        }

        cout << learner.Learn(words) << "\n";

        if (i++ > 1)
            break;
    }

    cout << "=== known words ===\n";

    for (const auto &word : learner.KnownWords())
    {
        cout << word << "\n";
    }

    return 0;
}
