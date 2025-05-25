#include "Movie.h"

unsigned Movie::nextId(1);

Movie::Movie() : Id(nextId++),title(), length(0), year(0), genre(Genre::ActionMovie), room(), date(), startTime(), ratings(MyVector<Rating>()), averageRating(0)
{
}


Movie::Movie(const MyString& title, unsigned length, unsigned year, Genre genre, Room room, const Date& date, const Hour& startTime, MyVector<Rating> ratings)
{
	Id = nextId++;
	setTitle(title);
	setLength(length);
	setYear(year);
	setGenre(genre);
	setRoom(room);
	setDate(date);
	setStartTime(startTime);
	setRatings(ratings);
}

Movie::Movie(unsigned Id, const MyString& title, unsigned length, unsigned year, Genre genre, Room room, const Date& date, const Hour& startTime)
{
	this->Id = Id;
	nextId++;
	setTitle(title);
	setLength(length);
	setYear(year);
	setGenre(genre);
	setRoom(room);
	setDate(date);
	setStartTime(startTime);
	setRatings(ratings);

}

unsigned Movie::getId() const
{
	return Id;
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
	size_t ratingsCount = ratings.getSize();
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

void Movie::writeToTextFile(std::ofstream& out) const {
	out << Id << "\n";
	writeStringToTextFile(out, title);
	out << length << "\n";
	out << year << "\n";
	out << static_cast<int>(genre) << "\n";
	room.writeToTextFile(out);
	date.writeToTextFile(out);
	startTime.writeToTextFile(out);

	// Write ratings
	out << ratings.getSize() << "\n";
	for (size_t i = 0; i < ratings.getSize(); i++) {
		ratings[i].writeToTextFile(out);
	}
}

void Movie::readFromTextFile(std::ifstream& in) {
	in >> Id;
	in.ignore();
	title = readStringFromTextFile(in);
	in >> length >> year;

	int genreInt;
	in >> genreInt;
	genre = static_cast<Genre>(genreInt);
	in.ignore();

	room.readFromTextFile(in);
	date.readFromTextFile(in);
	startTime.readFromTextFile(in);

	size_t ratingsCount;
	in >> ratingsCount;
	in.ignore();

	ratings.clear();
	for (size_t i = 0; i < ratingsCount; i++) {
		Rating rating;
		rating.readFromTextFile(in);
		ratings.push_back(rating);
	}
}
