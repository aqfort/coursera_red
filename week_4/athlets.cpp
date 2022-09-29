#include <iostream>
#include <list>
#include <algorithm>

using namespace std;

int main()
{
    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);

    const int MAX_ATHLETES = 100'000;
    using Position = list<int>::iterator;

    int n_athletes;
    cin >> n_athletes;

    list<int> row;
    vector<Position> athlete_pos(MAX_ATHLETES + 1, row.end());

    for (int i = 0; i < n_athletes; ++i)
    {
        int athlete, next_athlete;
        cin >> athlete >> next_athlete;
        athlete_pos[athlete] = row.insert(
            athlete_pos[next_athlete],
            athlete);
    }

    for (int x : row)
    {
        cout << x << '\n';
    }
    return 0;
}