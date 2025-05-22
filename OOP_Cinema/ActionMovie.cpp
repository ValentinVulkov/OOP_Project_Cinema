#include "ActionMovie.h"
#include <stdexcept>

ActionMovie::ActionMovie()
    : Movie("Untitled", 0.0, 0, 0, Genre::ActionMovie, 0, Date(), Hour()), actionIntensity(0) {}


ActionMovie::ActionMovie(const MyString& title, double rating, unsigned length,
    unsigned year, unsigned room, const Date& date,
    const Hour& startTime, unsigned intensity)
    : Movie(title, rating, length, year, Genre::ActionMovie, room, date, startTime),
    actionIntensity(intensity)
{
    if (intensity > MAX_ACTIONMOVIE_INTENSITY) {
        throw std::invalid_argument("Action intensity must be 0-20");
    }
}

unsigned ActionMovie::getIntensity() const {
    return actionIntensity;
}

void ActionMovie::setIntensity(unsigned newIntensity) {
    if (newIntensity > MAX_ACTIONMOVIE_INTENSITY) {
        throw std::invalid_argument("Action intensity must be 0-20");
    }
    actionIntensity = newIntensity;
}

double ActionMovie::calculatePrice() const {

    return DEFAULT_ACTIONMOVIE_PRICE + (actionIntensity * INTENSITY_PRICE_MULTIPLIER);
}

void ActionMovie::printInfo() const {
    std::cout << "=== Action Movie ===\n";
    Movie::printInfo();
    std::cout << "Action Intensity: " << actionIntensity << "/20\n"
        << "Ticket Price: " << calculatePrice() << " BGN\n";
}
