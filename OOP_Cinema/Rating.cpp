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

void Rating::writeToFile(std::ofstream& out) const {
    if (!out.good()) {
        throw std::runtime_error("Failed to write Rating: bad output stream");
    }

    // Write validation marker
    const char marker = 'T';
    out.write(&marker, 1);

    // Write username (using MyString's binary format)
    username.writeToFile(out);  

    // Write rating
    out.write(reinterpret_cast<const char*>(&rating), sizeof(rating));

    // Validate what we wrote
    if (out.fail()) {
        throw std::runtime_error("Failed to write Rating data");
    }
}

void Rating::readFromFile(std::ifstream& in) {
    if (!in.good()) {
        throw std::runtime_error("Failed to read Rating: bad input stream");
    }

    // Check marker
    char marker;
    in.read(&marker, 1);
    if (marker != 'T') {
        throw std::runtime_error("Invalid Rating data format");
    }

    // Read username
    username.readFromFile(in);  

    // Read rating
    in.read(reinterpret_cast<char*>(&rating), sizeof(rating));

    // Validate
    if (in.fail()) {
        throw std::runtime_error("Corrupted Rating data");
    }
    if (rating < 1 || rating > 10) {
        throw std::runtime_error("Invalid rating value in file");
    }
}