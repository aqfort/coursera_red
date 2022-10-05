#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>
#include <future>

using namespace std;

int SumToVectors(
    const vector<int> &one,
    const vector<int> &two)
{
    future<int> f = async([&one]
                          { return accumulate(begin(one), end(one), 0); });
    int result = accumulate(begin(two), end(two), 0);
    return result + f.get();
}

int main()
{
    cout << SumToVectors({1, 1, 1, 1}, {3, 3, 3}) << endl;
    return 0;
}
