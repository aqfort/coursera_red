#pragma once

#include <istream>
#include <ostream>
#include <set>
#include <list>
#include <vector>
#include <map>
#include <string>
#include <deque>
#include <string_view>

using namespace std;

class InvertedIndex
{
public:
    struct Info
    {
        size_t docid;
        size_t hitcount;
    };

    void Add(string &&document);
    vector<Info> Lookup(string_view word) const;

    const string &GetDocument(size_t id) const { return docs[id]; }
    const deque<string> &GetDocs() const { return docs; }

private:
    map<string_view, vector<Info>> index;
    deque<string> docs;
};

class SearchServer
{
public:
    SearchServer() = default;
    explicit SearchServer(istream &document_input);
    void UpdateDocumentBase(istream &document_input);
    void AddQueriesStream(istream &query_input, ostream &search_results_output);

private:
    InvertedIndex index;
};
