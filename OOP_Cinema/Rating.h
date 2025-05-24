#pragma once
#include "MyString.h"
class Rating
{
	MyString username;
	unsigned rating; // 1 to 10

public:
	Rating();
	Rating(const MyString& username, unsigned rating);

	const MyString& getUsername() const;
	unsigned getRating() const;

	void setUsername(const MyString& username);
	void setRating(unsigned rating);

	void printRatingInfo() const;
	~Rating() = default;

	void writeToFile(std::ofstream& out) const;
	void readFromFile(std::ifstream& in);
};

