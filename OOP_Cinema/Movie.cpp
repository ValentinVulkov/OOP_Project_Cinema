#include "Movie.h"

Movie::Movie() : title(), length(0), year(0), genre(Genre::ActionMovie), room(), date(), startTime(), ratings(MyVector<Rating>())
{
}

Movie::Movie(const MyString& title, unsigned length, unsigned year, Genre genre, Room room, const Date& date, const Hour& startTime, MyVector<Rating> ratings)
{
	setTitle(title);
	setLength(length);
	setYear(year);
	setGenre(genre);
	setRoom(room);
	setDate(date);
	setStartTime(startTime);
	setRatings(ratings);
}

const MyString& Movie::getTitle() const
{
	return title;
}

unsigned Movie::getLength() const
{
	return length;
}

unsigned Movie::getYear() const
{
	return year;
}

Genre Movie::getGenre() const
{
	return genre;
}

Room Movie::getRoom() const
{
	return room;
}

const Date& Movie::getDate() const
{
	return date;
}

const Hour& Movie::getStartTime() const
{
	return startTime;
}

const Hour& Movie::getEndTime() const
{
	return endTime;
}

const MyVector<Rating>& Movie::getRatings() const
{
	return ratings;
}

const double Movie::getAverageRating() const
{
	return averageRating;
}


void Movie::setTitle(const MyString& newTitle)
{
	if (newTitle.getSize() == 0) {
		throw std::invalid_argument("Title cannot be empty.");
	}
	title = newTitle;
}

void Movie::setLength(unsigned newLength)
{
	if (newLength == 0) {
		throw std::invalid_argument("Length must be greater than 0.");
	}
	length = newLength;
}

void Movie::setYear(unsigned newYear)
{
	if (newYear < 1888 || newYear > 2100) 
	{
		throw std::out_of_range("Invalid year.");
	}
	year = newYear;
}

void Movie::setGenre(Genre newGenre)
{
	genre = newGenre;
}

void Movie::setRoom(Room newRoom)
{
	room = newRoom;
}

void Movie::setDate(const Date& newDate)
{
	date = newDate;
}

void Movie::setStartTime(const Hour& newStartTime)
{
	startTime = newStartTime;
	endTime = startTime + length;
}

void Movie::setRatings(const MyVector<Rating> ratings)
{
	this->ratings = ratings;
	// Calculate average rating
	averageRating = calculateAverageRating(ratings);
}

double Movie::calculateAverageRating(const MyVector<Rating>& ratings) const
{
	double result = 0.0;
	unsigned ratingsCount = ratings.getSize();
	if (ratingsCount > 0) {
		double sum = 0;
		for (unsigned i = 0; i < ratingsCount; i++) {
			sum += ratings[i].getRating();
		}
		result = sum / ratingsCount;
	}
	else {
		result = 0; // No ratings, average is 0
	}
	return result;
}

void Movie::addRating(const Rating& rating) {
	ratings.push_back(rating);
	averageRating = calculateAverageRating(ratings);
}



void Movie::printInfo() const
{
	std::cout << "Title: " << title << std::endl;
	std::cout << "Length: " << length << " minutes" << std::endl;
	std::cout << "Year: " << year << std::endl;
	std::cout << "Genre: ";
	switch (genre) {
	case Genre::ActionMovie:
		std::cout << "Action Movie";
		break;
	case Genre::DramaMovie:
		std::cout << "Drama Movie";
		break;
	case Genre::DocumentaryMovie:
		std::cout << "Documentary Movie";
		break;
	}
	std::cout << std::endl;
	std::cout << "Room: " << room.getID() << std::endl;
	std::cout << "Date: " << date << std::endl;
	
	std::cout << ", Start Time: " << startTime << std::endl;
	std::cout << ", End Time: " << endTime << std::endl;
	std::cout << "Average Rating: " << averageRating << std::endl;
}
