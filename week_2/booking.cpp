#include <iostream>
#include <map>
#include <deque>

#include "test_runner.h"
#include "profile.h"

using namespace std;

class BookingManager {
public:
    BookingManager() = default;

    void book(const int64_t &time, const string &hotel_name, const int &client_id, const int &room_count) {
        Event event = Event(time, client_id, room_count);
    }

    int clients(const string &hotel_name) {
        return 0;
    }

    int rooms(const string &hotel_name) {
        return 0;
    }

private:
    struct Event {
        explicit Event(const int64_t &time, const int &client_id, const int &room_count) :
                time_(time), client_id_(client_id), room_count_(room_count) {}

        const int64_t time_ = 0;
        const int client_id_ = 0;
        const int room_count_ = 0;
    };

    class Hotel {
    public:
        Hotel() = default;

        void book(const int64_t &time, const int &client_id, const int &room_count) {

        }

        int clients() {

        }

    private:
        static int64_t current_time_;
        static const int64_t day_ = 86400;

        int room_count_sum_ = 0;
        map<int, int> clients_{};
        deque<Event> events_{};
    };

    map<string, Hotel> hotels_{};
};

void test();

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    {
        LOG_DURATION("TESTS")
        TestRunner runner;
        RUN_TEST(runner, test);
    }

    BookingManager manager;

    int query_count;
    cin >> query_count;

    for (int query_id = 0; query_id < query_count; query_id++) {
        string query_type;
        cin >> query_type;

        if (query_type == "BOOK") {
            int64_t time;
            string hotel_name;
            int client_id;
            int room_count;
            cin >> time >> hotel_name >> client_id >> room_count;
            manager.book(time, hotel_name, client_id, room_count);
        } else if (query_type == "ROOMS") {
            string hotel_name;
            cin >> hotel_name;
            cout << manager.rooms(hotel_name) << endl;
        } else {
            string hotel_name;
            cin >> hotel_name;
            cout << manager.clients(hotel_name) << endl;
        }
    }

    return 0;
}

void test() {
    BookingManager manager;

    ASSERT_EQUAL(manager.clients("Marriott"), 0);
    ASSERT_EQUAL(manager.rooms("Marriott"), 0);

    manager.book(10, "FourSeasons", 1, 2);
    manager.book(10, "Marriott", 1, 1);
    manager.book(86409, "FourSeasons", 2, 1);

    ASSERT_EQUAL(manager.clients("FourSeasons"), 2);
    ASSERT_EQUAL(manager.rooms("FourSeasons"), 3);
    ASSERT_EQUAL(manager.clients("Marriott"), 1);

    manager.book(86410, "Marriott", 2, 10);

    ASSERT_EQUAL(manager.rooms("FourSeasons"), 1);
    ASSERT_EQUAL(manager.rooms("Marriott"), 10);
}
