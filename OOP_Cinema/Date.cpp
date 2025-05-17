#include "Date.h"

Date::Date(int d, int m, int y) : day(d), month(m), year(y) {
    validate();
}

bool Date::isLeapYear() const {
    return (year % 400 == 0) || (year % 100 != 0 && year % 4 == 0);
}

int Date::daysInMonth() const {
    const int days[] = { 31, 28 + isLeapYear(), 31, 30, 31, 30,
                       31, 31, 30, 31, 30, 31 };
    return days[month - 1];
}

void Date::validate() const {
    if (year < 1900) throw std::invalid_argument("Invalid year");
    if (month < 1 || month > 12) throw std::invalid_argument("Invalid month");
    if (day < 1 || day > daysInMonth()) throw std::invalid_argument("Invalid day");
}

int Date::getDay() const { return day; }
int Date::getMonth() const { return month; }
int Date::getYear() const { return year; }

bool Date::operator<(const Date& other) const {
    if (year != other.year) return year < other.year;
    if (month != other.month) return month < other.month;
    return day < other.day;
}

bool Date::operator==(const Date& other) const {
    return year == other.year &&
        month == other.month &&
        day == other.day;
}

std::ostream& operator<<(std::ostream& os, const Date& date) {
    os << date.day << "/" << date.month << "/" << date.year;
    return os;
}

std::istream& operator>>(std::istream& is, Date& date) {
    char sep1, sep2;
    is >> date.day >> sep1 >> date.month >> sep2 >> date.year;
    if (sep1 != '/' || sep2 != '/') is.setstate(std::ios::failbit);
    else try { date.validate(); }
    catch (...) { is.setstate(std::ios::failbit); }
    return is;
}