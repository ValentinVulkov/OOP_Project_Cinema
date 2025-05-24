#pragma once
#include "Movie.h"

constexpr unsigned DEFAULT_DRAMAMOVIE_PRICE = 7;
constexpr unsigned COMEDY_ELEMENTS_ADDON = 3;

class DramaMovie : public Movie
{
	bool hasComedyElements;
public:
    DramaMovie();

    DramaMovie(const MyString& title, double rating, unsigned length,
        unsigned year, Room room, const Date& date,
        const Hour& startTime, bool comedyElements, MyVector<Rating> ratings);

    bool getHasComedyElements() const;
    void setHasComedyElements(bool hasComedyElements);

    double calculatePrice() const;
    void printInfo() const override;
	~DramaMovie() override = default;
};

