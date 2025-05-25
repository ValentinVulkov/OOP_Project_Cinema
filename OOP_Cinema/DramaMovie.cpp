#include "DramaMovie.h"
#include "Movie.h"




DramaMovie::DramaMovie() : Movie(), hasComedyElements(false)
{
}

DramaMovie::DramaMovie(const MyString& title, double rating, unsigned length, unsigned year, unsigned roomId, const Date& date, const Hour& startTime, bool comedyElements, MyVector<Rating> ratings)
	:Movie(title, length, year, Genre::DramaMovie, roomId, date, startTime, ratings)
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

void DramaMovie::writeToTextFile(std::ofstream& out) const
{
	Movie::writeToTextFile(out); // Write base class data
	out << (hasComedyElements ? "1" : "0") << "\n"; // Write comedy elements as 1 or 0
}

void DramaMovie::readFromTextFile(std::ifstream& in)
{
	Movie::readFromTextFile(in); // Read base class data
	int comedyFlag;
	in >> comedyFlag;
	hasComedyElements = (comedyFlag == 1); // Convert 1/0 to bool
	in.ignore(); // Skip newline character
}


