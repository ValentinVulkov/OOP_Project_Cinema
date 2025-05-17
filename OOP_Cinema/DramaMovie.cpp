#include "DramaMovie.h"
#include "Film.h"

DramaMovie::DramaMovie()
    : Film("Untitled", 0.0, 0, 0, Genre::DramaMovie, 0, Date(), Hour()), hasComedyElements(0) {}

DramaMovie::DramaMovie(const MyString& title, double rating, unsigned length, unsigned year, unsigned room, const Date& date, const Hour& startTime, bool comedyElements)
: Film(title, rating, length, year, Genre::ActionMovie, room, date, startTime),
hasComedyElements(comedyElements)
{

}

bool DramaMovie::getHasComedyElements() const
{
    return hasComedyElements;
}

void DramaMovie::setHasComedyElements(bool hasComedyElements)
{
	this->hasComedyElements = hasComedyElements;
}

double DramaMovie::calculatePrice() const
{
    if (hasComedyElements)
    {
		return DEFAULT_DRAMAMOVIE_PRICE + COMEDY_ELEMENTS_ADDON;
    }
    else
    {
        return DEFAULT_DRAMAMOVIE_PRICE;
    }
}

void DramaMovie::printInfo() const
{
	std::cout << "=== Drama Movie ===\n";
	Film::printInfo();
	std::cout << "Comedy Elements: " << (hasComedyElements ? "Yes" : "No") << "\n"
		<< "Ticket Price: " << calculatePrice() << " BGN\n";
}


