#include "search_server.h"
#include "iterator_range.h"
#include "profile.h"

#include <algorithm>
#include <iterator>
#include <sstream>
#include <iostream>

// Doubtful
vector<string_view> SplitIntoWords(string_view line)
{
    // https://www.cppstories.com/2018/07/string-view-perf-followup/
    vector<string_view> output;
    size_t first = 0;

    while (first < line.size())
    {
        const auto second = line.find_first_of(" ", first);

        if (first != second)
            output.emplace_back(line.substr(first, second - first));

        if (second == string_view::npos)
            break;

        first = second + 1;
    }

    return output;
}

// Good
SearchServer::SearchServer(istream &document_input)
{
    // LOG_DURATION("SearchServer");

    UpdateDocumentBase(document_input);
}

// Initially slow: check Add-method
void SearchServer::UpdateDocumentBase(istream &document_input)
{
    LOG_DURATION("UpdateDocumentBase");

    InvertedIndex new_index;

    for (string current_document; getline(document_input, current_document);)
    {
        new_index.Add(move(current_document)); // Cause
    }

    index = move(new_index);
}

// Initially slow
void SearchServer::AddQueriesStream(
    istream &query_input, ostream &search_results_output)
{
    LOG_DURATION("AddQueriesStream");

    const deque<string> &docs = index.GetDocs();
    vector<size_t> docid_count(docs.size());
    vector<size_t> docids(docs.size());

    for (string current_query; getline(query_input, current_query);)
    {
        vector<string_view> words = SplitIntoWords(current_query);
        docid_count.assign(docid_count.size(), 0);

        for (const auto &word : words)
        {
            for (const auto &[docid, hitcount] : index.Lookup(word))
            {
                docid_count[docid] += hitcount;
            }
        }

        for (size_t i = 0; i < docids.size(); i++)
        {
            docids[i] = i;
        }

        partial_sort(
            begin(docids),
            Head(docids, 5).end(),
            end(docids),
            [&docid_count](int64_t lhs, int64_t rhs)
            {
                return make_pair(docid_count[lhs], -lhs) > make_pair(docid_count[rhs], -rhs);
            });

        search_results_output << current_query << ':';
        for (size_t docid : Head(docids, 5))
        {
            const size_t hit_count = docid_count[docid];
            if (hit_count == 0)
            {
                break;
            }

            search_results_output << " {"
                                  << "docid: " << docid << ", "
                                  << "hitcount: " << hit_count << '}';
        }

        search_results_output << endl;
    }
}

// Initially slow: fixed
void InvertedIndex::Add(string &&document)
{
    LOG_DURATION("Add");

    docs.push_back(move(document));

    const size_t docid = docs.size() - 1;
    for (const auto &word : SplitIntoWords(docs.back()))
    {
        // TO-DO: slow, check it
        // index[word].push_back(docid);

        vector<Info> &info = index[word];

        if (!info.empty() && info.back().docid == docid)
        {
            info.back().hitcount += 1;
        }
        else
        {
            info.push_back({docid, 1}); // Copy elision should work
        }
    }
}

// Good
vector<InvertedIndex::Info> InvertedIndex::Lookup(string_view word) const
{
    // LOG_DURATION("Lookup");

    if (auto it = index.find(word); it != index.end())
    {
        return it->second;
    }
    else
    {
        return {};
    }
}
