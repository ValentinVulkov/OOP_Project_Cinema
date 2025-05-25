#include "Hour.h"

Hour::Hour() : hour(0), minute(0)
{
}

Hour::Hour(int h, int m) : hour(h), minute(m) {
    validate();
}

void Hour::validate() const {
    if (hour < 0 || hour > 23) throw std::invalid_argument("Invalid hour");
    if (minute < 0 || minute > 59) throw std::invalid_argument("Invalid minute");
}

int Hour::getHour() const { return hour; }
int Hour::getMinute() const { return minute; }

Hour Hour::operator+(const Hour& other) const {
    int totalMinutes = hour * 60 + minute + other.hour * 60 + other.minute;
    totalMinutes %= (24 * 60);
    if (totalMinutes < 0) totalMinutes += 24 * 60;
    return Hour(totalMinutes / 60, totalMinutes % 60);
}

// Add minutes to Hour (fixed implementation)
Hour Hour::operator+(int minutes) const {
    int totalMinutes = hour * 60 + minute + minutes;
    totalMinutes %= (24 * 60);
    if (totalMinutes < 0) totalMinutes += 24 * 60;
    return Hour(totalMinutes / 60, totalMinutes % 60);
}

bool Hour::operator<(const Hour& other) const {
    if (hour != other.hour) return hour < other.hour;
    return minute < other.minute;
}

bool Hour::operator==(const Hour& other) const {
    return hour == other.hour && minute == other.minute;
}

Hour Hour::addMinutes(int minutes) const {
    int total = hour * 60 + minute + minutes;
    total %= (24 * 60);
    if (total < 0) total += 24 * 60;
    return Hour(total / 60, total % 60);
}

std::ostream& operator<<(std::ostream& os, const Hour& h) {
    os << h.hour << ":" << (h.minute < 10 ? "0" : "") << h.minute;
    return os;
}

std::istream& operator>>(std::istream& is, Hour& h) {
    char sep;
    is >> h.hour >> sep >> h.minute;
    if (sep != ':') is.setstate(std::ios::failbit);
    else try { h.validate(); }
    catch (...) { is.setstate(std::ios::failbit); }
    return is;
}



void Hour::writeToTextFile(std::ofstream& out) const {
    out << hour << " " << minute << "\n";  // Space-separated values
}

void Hour::readFromTextFile(std::ifstream& in) {
    in >> hour >> minute;
    in.ignore();  // Skip the newline after reading
    validate();   // Verify the time is valid
}