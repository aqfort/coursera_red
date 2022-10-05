#include "test_runner.h"
#include "profile.h"

#include <map>
#include <string>
#include <algorithm>
#include <future>
#include <vector>
#include <list>
#include <sstream>
#include <iterator>
#include <string_view>
#include <regex>
#include <functional>

using namespace std;

struct Stats
{
    map<string, int> word_frequences;

    void operator+=(const Stats &other)
    {
        for (auto &[word, frequency] : other.word_frequences)
        {
            word_frequences[word] += frequency;
        }
    }
};

Stats ExploreLine(const set<string> &key_words, const string &line)
{
    Stats stats;
    vector<string> words;
    // regex pattern(R"(\s+)");
    // move(sregex_token_iterator(line.begin(), line.end(), pattern, -1),
    //      sregex_token_iterator(), back_inserter(words));

    istringstream iss(line);

    copy(istream_iterator<string>(iss),
         istream_iterator<string>(),
         back_inserter(words));

    for (const string &word : words)
    {
        if (key_words.count(word) > 0)
        {
            stats.word_frequences[word]++;
        }
    }

    return stats;
}

Stats ExplorePile(const set<string> &key_words, vector<string> lines)
{
    Stats stats;

    for (const string &line : lines)
    {
        stats += ExploreLine(key_words, line);
    }

    return stats;
}

// Stats ExploreKeyWordsSingleThread(const set<string> &key_words, istream &input);

Stats ExploreKeyWords(const set<string> &key_words, istream &input)
{
    // Implement this function
    // key_words и input будут переданы по ссылке, а не скопированы
    // return async(ExploreKeyWordsSingleThread, ref(key_words), ref(input)).get();
    Stats stats;

    // list<future<Stats>> futures;
    vector<future<Stats>> futures;

    const size_t lines_limit = 5000;

    vector<string> pile;
    pile.reserve(lines_limit);

    string line;

    while (getline(input, line))
    {
        pile.push_back(move(line));
        if (pile.size() >= lines_limit)
        {
            futures.push_back(async(ExplorePile, ref(key_words), move(pile)));
            pile.reserve(lines_limit);
        }
    }

    if (!pile.empty())
    {
        stats += ExplorePile(key_words, move(pile));
    }

    for (auto &item : futures)
    {
        stats += item.get();
    }

    return stats;
}

void TestBasic()
{
    const set<string> key_words = {"yangle", "rocks", "sucks", "all"};

    stringstream ss;
    ss << "this new yangle service really rocks\n";
    ss << "It sucks when yangle isn't available\n";
    ss << "10 reasons why yangle is the best IT company\n";
    ss << "yangle rocks others suck\n";
    ss << "Goondex really sucks, but yangle rocks. Use yangle\n";

    const auto stats = ExploreKeyWords(key_words, ss);
    const map<string, int> expected = {
        {"yangle", 6},
        {"rocks", 2},
        {"sucks", 1}};
    ASSERT_EQUAL(stats.word_frequences, expected);
}

int main()
{
    TestRunner tr;
    RUN_TEST(tr, TestBasic);
}
