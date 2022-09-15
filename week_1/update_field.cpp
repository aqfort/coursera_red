#include "airline_ticket.h"
// #include "test_runner.h"

#include "../test_runner_lib/test_runner.h"

#include <iomanip>
#include <map>

using namespace std;

bool operator<(const Date &lhs, const Date &rhs)
{
    return make_tuple(lhs.year, lhs.month, lhs.day) < make_tuple(rhs.year, rhs.month, rhs.day);
}

bool operator<(const Time &lhs, const Time &rhs)
{
    return make_tuple(lhs.hours, lhs.minutes) < make_tuple(rhs.hours, rhs.minutes);
}

ostream &operator<<(ostream &stream, const Date &date)
{
    stream << setfill('0') << setw(4) << date.year << '-'
           << setfill('0') << setw(2) << date.month << '-'
           << setfill('0') << setw(2) << date.day;
    return stream;
}

ostream &operator<<(ostream &stream, const Time &time)
{
    stream << setfill('0') << setw(2) << time.hours << ':'
           << setfill('0') << setw(2) << time.minutes;
    return stream;
}

bool operator!=(const Date &lhs, const Date &rhs)
{
    return make_tuple(lhs.year, lhs.month, lhs.day) != make_tuple(rhs.year, rhs.month, rhs.day);
}

bool operator!=(const Time &lhs, const Time &rhs)
{
    return make_tuple(lhs.hours, lhs.minutes) != make_tuple(rhs.hours, rhs.minutes);
}

bool operator==(const Date &lhs, const Date &rhs)
{
    return make_tuple(lhs.year, lhs.month, lhs.day) == make_tuple(rhs.year, rhs.month, rhs.day);
}

bool operator==(const Time &lhs, const Time &rhs)
{
    return make_tuple(lhs.hours, lhs.minutes) == make_tuple(rhs.hours, rhs.minutes);
}

Date ParseDateFromString(const string &string_input)
{
    istringstream string_stream(string_input);
    bool flag = true;

    int new_year(0);
    int new_month(0);
    int new_day(0);

    flag = flag && (string_stream >> new_year);
    flag = flag && (string_stream.peek() == '-');
    string_stream.ignore(1);

    flag = flag && (string_stream >> new_month);
    flag = flag && (string_stream.peek() == '-');
    string_stream.ignore(1);

    flag = flag && (string_stream >> new_day);
    flag = flag && (string_stream.eof());

    if (!flag)
    {
        throw runtime_error("Wrong date format: " + string_input);
    }

    Date result{};
    result.year = new_year;
    result.month = new_month;
    result.day = new_day;

    return result;
}

Time ParseTimeFromString(const string &string_input)
{
    istringstream string_stream(string_input);
    bool flag = true;

    int new_hours(0);
    int new_minutes(0);

    flag = flag && (string_stream >> new_hours);
    flag = flag && (string_stream.peek() == ':');
    string_stream.ignore(1);

    flag = flag && (string_stream >> new_minutes);
    flag = flag && (string_stream.eof());

    if (!flag)
    {
        throw runtime_error("Wrong time format: " + string_input);
    }

    Time result{};
    result.hours = new_hours;
    result.minutes = new_minutes;

    return result;
}

istream &operator>>(istream &stream, Date &date)
{
    string string_input;
    stream >> string_input;
    date = ParseDateFromString(string_input);
    return stream;
}

istream &operator>>(istream &stream, Time &time)
{
    string string_input;
    stream >> string_input;
    time = ParseTimeFromString(string_input);
    return stream;
}

#define UPDATE_FIELD(ticket, field, values)  \
    {                                        \
        auto it = (values).find(#field);     \
        if (it != (values).end())            \
        {                                    \
            stringstream stream(it->second); \
            stream >> (ticket).field;        \
        }                                    \
    }

void TestUpdate()
{
    AirlineTicket t;
    t.price = 0;

    const map<string, string> updates1 = {
        {"departure_date", "2018-2-28"},
        {"departure_time", "17:40"},
    };
    UPDATE_FIELD(t, departure_date, updates1);
    UPDATE_FIELD(t, departure_time, updates1);
    UPDATE_FIELD(t, price, updates1);

    ASSERT_EQUAL(t.departure_date, (Date{2018, 2, 28}));
    ASSERT_EQUAL(t.departure_time, (Time{17, 40}));
    ASSERT_EQUAL(t.price, 0);

    const map<string, string> updates2 = {
        {"price", "12550"},
        {"arrival_time", "20:33"},
    };
    UPDATE_FIELD(t, departure_date, updates2);
    UPDATE_FIELD(t, departure_time, updates2);
    UPDATE_FIELD(t, arrival_time, updates2);
    UPDATE_FIELD(t, price, updates2);

    // updates2 не содержит ключей "departure_date" и "departure_time", поэтому
    // значения этих полей не должны измениться
    ASSERT_EQUAL(t.departure_date, (Date{2018, 2, 28}));
    ASSERT_EQUAL(t.departure_time, (Time{17, 40}));
    ASSERT_EQUAL(t.price, 12550);
    ASSERT_EQUAL(t.arrival_time, (Time{20, 33}));
}

int main()
{
    TestRunner tr;
    RUN_TEST(tr, TestUpdate);
}
