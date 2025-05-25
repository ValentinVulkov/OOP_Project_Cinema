#include "ActionMovie.h"
#include <stdexcept>




ActionMovie::ActionMovie() : Movie(), actionIntensity(0) {}

ActionMovie::ActionMovie(const MyString& title, double rating, unsigned length, unsigned year, unsigned roomId, const Date& date, const Hour& startTime, MyVector<Rating> ratings, unsigned intensity)
: Movie(title, length, year, Genre::ActionMovie, roomId, date, startTime, ratings)
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

void ActionMovie::writeToTextFile(std::ofstream& out) const {
    Movie::writeToTextFile(out); // Write base class data
    out << actionIntensity << "\n";
}

void ActionMovie::readFromTextFile(std::ifstream& in) {
    Movie::readFromTextFile(in); // Read base class data
    in >> actionIntensity;
    in.ignore(); // Skip newline
}
