#ifndef HOUR_H
#define HOUR_H

#include <iostream>
#include <stdexcept>

class Hour {
private:
    int hour;
    int minute;

    void validate() const;

public:
	Hour();
    Hour(int h, int m);

    int getHour() const;
    int getMinute() const;

    Hour operator+(const Hour& rhs) const;
    Hour operator+(int additionalMinutes) const;
    bool operator<(const Hour& other) const;
    bool operator==(const Hour& other) const;

    Hour addMinutes(int minutes) const;

    friend std::ostream& operator<<(std::ostream& os, const Hour& h);
    friend std::istream& operator>>(std::istream& is, Hour& h);
	~Hour() = default;
};

#endif // HOUR_H

