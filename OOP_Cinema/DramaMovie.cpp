#include "DramaMovie.h"
#include "Movie.h"




DramaMovie::DramaMovie() : Movie(), hasComedyElements(false)
{
}

DramaMovie::DramaMovie(const MyString& title, double rating, unsigned length, unsigned year, Room room, const Date& date, const Hour& startTime, bool comedyElements, MyVector<Rating> ratings)
	:Movie(title, length, year, Genre::DramaMovie, room, date, startTime, ratings)
{
	setHasComedyElements(comedyElements);
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
	Movie::printInfo();
	std::cout << "Comedy Elements: " << (hasComedyElements ? "Yes" : "No") << "\n"
		<< "Ticket Price: " << calculatePrice() << " BGN\n";
}


