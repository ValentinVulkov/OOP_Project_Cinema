#include "ActionMovie.h"
#include <stdexcept>




ActionMovie::ActionMovie() : Movie(), actionIntensity(0) {}

ActionMovie::ActionMovie(const MyString& title, double rating, unsigned length, unsigned year, Room room, const Date& date, const Hour& startTime, MyVector<Rating> ratings, unsigned intensity)
: Movie(title, length, year, Genre::ActionMovie, room, date, startTime, ratings)
{
	setIntensity(intensity);
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
