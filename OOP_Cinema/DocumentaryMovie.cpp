#include "DocumentaryMovie.h"

DocumentaryMovie::DocumentaryMovie() : Movie(), theme(), isBasedOnTrueEvents(false)
{
}

DocumentaryMovie::DocumentaryMovie(const MyString& title, double rating, unsigned length, unsigned year, unsigned roomId, const Date& date, const Hour& startTime, MyVector<Rating> ratings, const MyString& theme, bool isBasedOnTrueEvents)
	:Movie(title, length, year, Genre::DocumentaryMovie, roomId , date, startTime, ratings)
{
	setTheme(theme);
	setIsBasedOnTrueEvents(isBasedOnTrueEvents);

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

void DocumentaryMovie::writeToTextFile(std::ofstream& out) const
{
	Movie::writeToTextFile(out); // Write base class data
	out << theme << "\n";
	out	<< (isBasedOnTrueEvents ? "1" : "0") << "\n"; // 1 for true, 0 for false
}

void DocumentaryMovie::readFromTextFile(std::ifstream& in)
{
	Movie::readFromTextFile(in); // Read base class data
	in >> theme;
	int trueEventsFlag;
	in >> trueEventsFlag;
	in.ignore(); // Skip newline
	isBasedOnTrueEvents = (trueEventsFlag == 1);
}
