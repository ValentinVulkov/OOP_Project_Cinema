#ifndef DATE_H
#define DATE_H

#include <iostream>
#include <stdexcept>

class Date {
private:
    int day;
    int month;
    int year;

    bool isLeapYear() const;
    int daysInMonth() const;
    void validate() const;

public:
    Date();
    Date(int d, int m, int y);

    // Getters
    int getDay() const;
    int getMonth() const;
    int getYear() const;

    // Comparison operators
    bool operator<(const Date& other) const;
    bool operator==(const Date& other) const;

    // Stream operators
    friend std::ostream& operator<<(std::ostream& os, const Date& date);
    friend std::istream& operator>>(std::istream& is, Date& date);
	~Date() = default;
};

#endif // DATE_H

