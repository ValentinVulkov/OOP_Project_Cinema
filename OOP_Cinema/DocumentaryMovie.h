#pragma once
#include "Film.h"

constexpr unsigned DEFAULT_DOCUMENTARYMOVIE_PRICE = 5;
constexpr unsigned TRUE_EVENTS_ADDON = 2;

class DocumentaryMovie : public Film
{
	MyString theme;
	bool isBasedOnTrueEvents;

public:
	DocumentaryMovie();
	DocumentaryMovie(const MyString& title, double rating, unsigned length,
		unsigned year, unsigned room, const Date& date,
		const Hour& startTime, const MyString& theme, bool isBasedOnTrueEvents);

	MyString getTheme() const;
	void setTheme(const MyString& newTheme);
	bool getIsBasedOnTrueEvents() const;
	void setIsBasedOnTrueEvents(bool newIsBasedOnTrueEvents);

	double calculatePrice() const;
	void printInfo() const override;
};

