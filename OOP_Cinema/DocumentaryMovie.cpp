#include "DocumentaryMovie.h"

DocumentaryMovie::DocumentaryMovie() : Movie(), theme(), isBasedOnTrueEvents(false)
{
}

DocumentaryMovie::DocumentaryMovie(const MyString& title, double rating, unsigned length, unsigned year, unsigned room, const Date& date, 
const Hour& startTime, const MyString& theme, bool isBasedOnTrueEvents) 
: Movie(title, rating, length, year, Genre::DocumentaryMovie, room, date, startTime), theme(theme), isBasedOnTrueEvents(isBasedOnTrueEvents)
{
}


MyString DocumentaryMovie::getTheme() const
{
	return theme;
}

void DocumentaryMovie::setTheme(const MyString& newTheme)
{
	this->theme = newTheme;
}

bool DocumentaryMovie::getIsBasedOnTrueEvents() const
{
	return isBasedOnTrueEvents;
}

void DocumentaryMovie::setIsBasedOnTrueEvents(bool newIsBasedOnTrueEvents)
{
	this->isBasedOnTrueEvents = newIsBasedOnTrueEvents;

}

double DocumentaryMovie::calculatePrice() const
{
	if (isBasedOnTrueEvents)
	{
		return DEFAULT_DOCUMENTARYMOVIE_PRICE + TRUE_EVENTS_ADDON;
	}
	else
	{
		return DEFAULT_DOCUMENTARYMOVIE_PRICE;
	}
}

void DocumentaryMovie::printInfo() const
{
	std::cout << "=== Documentary Movie ===\n";
	Movie::printInfo();
	std::cout << "Theme: " << theme << "\n"
		<< "Based on True Events: " << (isBasedOnTrueEvents ? "Yes" : "No") << "\n"
		<< "Ticket Price: " << calculatePrice() << " BGN\n";
}
