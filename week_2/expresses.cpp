#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <set>

using namespace std;

class RouteManager {
public:
    void AddRoute(const int &start, const int &finish) {
        this->reachable_lists_[start].emplace(finish);
        this->reachable_lists_[finish].emplace(start);
    }

    [[nodiscard]] int FindNearestFinish(const int &start, const int &finish) const {
        int result = abs(finish - start);

        if (this->reachable_lists_.count(start) < 1) {
            return result;
        }

        const set<int> &reachable_stations = reachable_lists_.at(start);

        const auto finish_pos = reachable_stations.lower_bound(finish);

        if (finish_pos != end(reachable_stations)) {
            result = min(result, abs(finish - *finish_pos));
        }

        if (finish_pos != begin(reachable_stations)) {
            result = min(result, abs(finish - *prev(finish_pos)));
        }

        return result;
    }

private:
    map<int, set<int>> reachable_lists_;
};


int main() {
    RouteManager routes;

    int query_count;
    cin >> query_count;

    for (int query_id = 0; query_id < query_count; ++query_id) {
        string query_type;
        cin >> query_type;
        int start, finish;
        cin >> start >> finish;
        if (query_type == "ADD") {
            routes.AddRoute(start, finish);
        } else if (query_type == "GO") {
            cout << routes.FindNearestFinish(start, finish) << "\n";
        }
    }

    return 0;
}
