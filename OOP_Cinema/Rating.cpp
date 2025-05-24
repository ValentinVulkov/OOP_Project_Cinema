#include "Rating.h"

Rating::Rating() : username(), rating(0)
{
}

Rating::Rating(const MyString& username, unsigned rating)
{
	setUsername(username);
	setRating(rating);

}

const MyString& Rating::getUsername() const
{
	return username;
}

unsigned Rating::getRating() const
{
	return rating;
}

void Rating::setUsername(const MyString& username)
{
	this->username = username;
}

void Rating::setRating(unsigned rating)
{
	if (rating < 1 || rating > 10) {
		throw std::invalid_argument("Rating must be between 1 and 10");
	}
	this->rating = rating;
}

void Rating::printRatingInfo() const
{
	std::cout << "Rating by " << username << ": " << rating << "/10\n";
}
