#pragma once
#include "Movie.h"

constexpr unsigned DEFAULT_DOCUMENTARYMOVIE_PRICE = 5;
constexpr unsigned TRUE_EVENTS_ADDON = 2;

class DocumentaryMovie : public Movie
{
	MyString theme;
	bool isBasedOnTrueEvents;

public:
	DocumentaryMovie();
	DocumentaryMovie(const MyString& title, double rating, unsigned length,
		unsigned year, unsigned roomId, const Date& date,
		const Hour& startTime, MyVector<Rating> ratings, const MyString& theme, bool isBasedOnTrueEvents);

	// Getters and Setters

	MyString getTheme() const;
	void setTheme(const MyString& newTheme);
	bool getIsBasedOnTrueEvents() const;
	void setIsBasedOnTrueEvents(bool newIsBasedOnTrueEvents);

	double calculatePrice() const;
	void printInfo() const override;
	~DocumentaryMovie() override = default;

	void writeToTextFile(std::ofstream& out) const override;
	void readFromTextFile(std::ifstream& in) override;
};

