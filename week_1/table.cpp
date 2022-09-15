#include "test_runner.h"

using namespace std;

template <typename T>
class Table
{
private:
    vector<vector<T>> data;

public:
    Table(const size_t &dimension_1, const size_t &dimension_2)
    {
        Resize(dimension_1, dimension_2);
    }

    const vector<T> &operator[](size_t dimension) const
    {
        return data[dimension];
    }

    vector<T> &operator[](size_t dimension)
    {
        return data[dimension];
    }

    [[nodiscard]] pair<size_t, size_t> Size() const
    {
        if (!data.empty() && !data[0].empty())
        {
            return {data.size(), data[0].size()};
        }

        return {0, 0};
    }

    void Resize(size_t dimension_1, size_t dimension_2)
    {
        data.resize(dimension_1);
        for (auto &i : data)
        {
            i.resize(dimension_2);
        }
    }
};

void TestTable()
{
    Table<int> t(1, 1);
    ASSERT_EQUAL(t.Size().first, 1u);
    ASSERT_EQUAL(t.Size().second, 1u);
    t[0][0] = 42;
    ASSERT_EQUAL(t[0][0], 42);
    t.Resize(3, 4);
    ASSERT_EQUAL(t.Size().first, 3u);
    ASSERT_EQUAL(t.Size().second, 4u);
}

int main()
{
    TestRunner tr;
    RUN_TEST(tr, TestTable);
    return 0;
}
