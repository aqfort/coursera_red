#include "test_runner.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <queue>
#include <stdexcept>
#include <set>

using namespace std;

template <class T>
class ObjectPool
{
public:
    T *Allocate()
    {
        T *temp;

        if (deallocated.empty())
        {
            temp = new T;
        }
        else
        {
            temp = deallocated.front();
            deallocated.pop();
        }

        allocated.insert(temp);

        return temp;
    }

    T *TryAllocate()
    {
        if (deallocated.empty())
        {
            return nullptr;
        }

        T *temp = deallocated.front();
        deallocated.pop();

        allocated.insert(temp);

        return temp;
    }

    void Deallocate(T *object)
    {
        auto it = allocated.find(object);
        if (it == allocated.end())
        {
            throw invalid_argument("");
        }

        deallocated.emplace(*it);
        allocated.erase(it);
    }

    ~ObjectPool()
    {
        for (auto &item : allocated)
        {
            delete item;
        }

        while (!deallocated.empty())
        {
            auto temp = deallocated.front();
            deallocated.pop();
            delete temp;
        }
    }

private:
    set<T *> allocated;
    queue<T *> deallocated;
};

void TestObjectPool()
{
    ObjectPool<string> pool;

    auto p1 = pool.Allocate();
    auto p2 = pool.Allocate();
    auto p3 = pool.Allocate();

    *p1 = "first";
    *p2 = "second";
    *p3 = "third";

    pool.Deallocate(p2);
    ASSERT_EQUAL(*pool.Allocate(), "second");

    pool.Deallocate(p3);
    pool.Deallocate(p1);
    ASSERT_EQUAL(*pool.Allocate(), "third");
    ASSERT_EQUAL(*pool.Allocate(), "first");

    pool.Deallocate(p1);
}

int main()
{
    TestRunner tr;
    RUN_TEST(tr, TestObjectPool);

    return 0;
}
