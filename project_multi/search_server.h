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
#include <mutex>
#include <thread>
#include <future>

using namespace std;

// Реализуйте шаблон Synchronized<T>.
// Метод GetAccess должен возвращать структуру, в которой есть поле T& value.
template <typename T>
class Synchronized
{
public:
    explicit Synchronized(T initial = T()) : value(move(initial)) {}

    struct Access
    {
        T &ref_to_value;
        lock_guard<mutex> guard;
    };

    Access GetAccess()
    {
        return {value, lock_guard(mutex_local)};
    }

private:
    T value;
    mutex mutex_local;
};

class InvertedIndex
{
public:
    struct Info
    {
        size_t docid;
        size_t hitcount;
    };

    InvertedIndex() = default;
    explicit InvertedIndex(istream &document_input);
    void Add(string &&document);
    const vector<Info> &Lookup(string_view word) const;
    const deque<string> &GetDocs() const { return docs; }

private:
    map<string_view, vector<Info>> index;
    deque<string> docs;
};

class SearchServer
{
public:
    SearchServer() = default;
    explicit SearchServer(istream &document_input)
        : index(InvertedIndex(document_input)) {}
    void UpdateDocumentBase(istream &document_input);
    void AddQueriesStream(istream &query_input, ostream &search_results_output);

private:
    Synchronized<InvertedIndex> index;
    vector<future<void>> futures;

    // void UpdateDocumentBaseSynchronized(
    //     istream &document_input,
    //     Synchronized<InvertedIndex> &index_sync);

    // void AddQueriesStreamSynchronized(
    //     istream &query_input,
    //     ostream &search_results_output,
    //     Synchronized<InvertedIndex> &index_sync);
};
