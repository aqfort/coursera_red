#include <iostream>
#include <cstdint>
#include <deque>
#include "test_runner.h"
#include "profile.h"

using namespace std;

class BookingManager {
public:
    BookingManager() {

    }

    void book(const int64_t &time, const string &hotel_name, const int &client_id, const int &room_count) {

    }

    int clients(const string &hotel_name) {
        return 0;
    }

    int rooms(const string &hotel_name) {
        return 0;
    }

private:
    deque<int> data;
};

int bookingMachine() {
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
        } else if (query_type == "CLIENTS") {
            string hotel_name;

            cin >> hotel_name;

            cout << manager.clients(hotel_name) << endl;
        } else if (query_type == "ROOMS") {
            string hotel_name;

            cin >> hotel_name;

            cout << manager.rooms(hotel_name) << endl;
        } else {
            return 1;
        }
    }

    return 0;
}

void checkNumericLimits() {
    cout << "time: signed\n\t" << 1E18 << "\n\t";
    cout << numeric_limits<int64_t>::max() << "\n";

    cout << "client_id: unsigned\n\t" << 1E9 << "\n\t";
    cout << numeric_limits<int>::max() << "\n";
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

int main(int argc, char **argv) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

//    {
//        LOG_DURATION("LIMITS")
//        checkNumericLimits();
//    }

    {
        LOG_DURATION("TESTS")
        TestRunner runner;
        RUN_TEST(runner, test);
    }

//    {
//        LOG_DURATION("BOOKING")
//        int result = bookingMachine();
//
//        if (result == 1) {
//            cerr << "ERROR\n";
//        }
//    }

    return 0;
}