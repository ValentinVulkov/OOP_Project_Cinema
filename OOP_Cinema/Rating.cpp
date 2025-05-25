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

bool Rating::isValidRating(unsigned rating) {
    return rating >= 1 && rating <= 10;
}

void Rating::printRatingInfo() const
{
	std::cout << "Rating by " << username << ": " << rating << "/10\n";
}

void Rating::writeToTextFile(std::ofstream& out) const {
    if (!out.good()) throw std::runtime_error("Output stream error");
    out << username.c_str() << "\n" << rating << "\n";
}

void Rating::readFromTextFile(std::ifstream& in) {
    if (!in.good()) throw std::runtime_error("Input stream error");

    // Read username line
    char buffer[256];
    in.getline(buffer, sizeof(buffer));
    if (in.fail()) throw std::runtime_error("Failed to read username");
    username = MyString(buffer);

    // Read rating line
    in >> rating;
    if (in.fail()) throw std::runtime_error("Failed to read rating value");
    in.ignore(); // Consume newline

    // Validate
    if (!isValidRating(rating)) {
        throw std::out_of_range("Rating must be 1-10");
    }
}