#pragma once
#include "Film.h"

constexpr unsigned DEFAULT_DRAMAMOVIE_PRICE = 7;
constexpr unsigned COMEDY_ELEMENTS_ADDON = 3;

class DramaMovie : public Film
{
	bool hasComedyElements;
public:
    DramaMovie();

    DramaMovie(const MyString& title, double rating, unsigned length,
        unsigned year, unsigned room, const Date& date,
        const Hour& startTime, bool comedyElements);

    bool getHasComedyElements() const;
    void setHasComedyElements(bool hasComedyElements);

    double calculatePrice() const;
    void printInfo() const override;
};

