#include "stats.h"

using namespace std;

Stats::Stats()
{
    method_stats = {{"GET", 0}, {"POST", 0}, {"PUT", 0}, {"DELETE", 0}, {"UNKNOWN", 0}};
    uri_stats = {{"/", 0}, {"/order", 0}, {"/product", 0}, {"/basket", 0}, {"/help", 0}, {"unknown", 0}};
}

void Stats::AddMethod(string_view method)
{
    if (method_stats.find(method) != method_stats.end())
    {
        method_stats[method]++;
    }
    else
    {
        method_stats["UNKNOWN"]++;
    }
}

void Stats::AddUri(string_view uri)
{
    if (uri_stats.find(uri) != uri_stats.end())
    {
        uri_stats[uri]++;
    }
    else
    {
        uri_stats["unknown"]++;
    }
}

const map<string_view, int> &Stats::GetMethodStats() const
{
    return method_stats;
}

const map<string_view, int> &Stats::GetUriStats() const
{
    return uri_stats;
}

HttpRequest ParseRequest(string_view line)
{
    HttpRequest parse;
    line.remove_prefix(line.find_first_not_of(" "));

    parse.method = line.substr(0, line.find(" "));
    line.remove_prefix(min(line.find(" ") + 1, line.size()));

    parse.uri = line.substr(0, line.find(" "));
    line.remove_prefix(min(line.find(" ") + 1, line.size()));

    parse.protocol = line.substr(0, line.find(" "));

    return parse;
}

// #include "stats.h"

// void Stats::AddMethod(string_view method) {
//   methods.Add(method);
// }

// void Stats::AddUri(string_view uri) {
//   uris.Add(uri);
// }

// const map<string_view, int>& Stats::GetMethodStats() const {
//   return methods.GetValues();
// }

// const map<string_view, int>& Stats::GetUriStats() const {
//   return uris.GetValues();
// }

// void LeftStrip(string_view& sv) {
//   while (!sv.empty() && isspace(sv[0])) {
//     sv.remove_prefix(1);
//   }
// }

// string_view ReadToken(string_view& sv) {
//   LeftStrip(sv);

//   auto pos = sv.find(' ');
//   auto result = sv.substr(0, pos);
//   sv.remove_prefix(pos != sv.npos ? pos : sv.size());
//   return result;
// }

// HttpRequest ParseRequest(string_view line) {
//   auto method = ReadToken(line);
//   auto uri = ReadToken(line);
//   return {method, uri, ReadToken(line)};
// }

// void StatPiece::Add(string_view value) {
//   if (auto it = counts.find(value); it != counts.end()) {
//     ++it->second;
//   } else {
//     ++counts[default_key];
//   }
// }
