#pragma once
#include "Film.h"
#include "Date.h"
#include "Hour.h"

constexpr unsigned DEFAULT_ACTIONMOVIE_PRICE = 9;
constexpr unsigned MAX_ACTIONMOVIE_INTENSITY = 20;
constexpr double INTENSITY_PRICE_MULTIPLIER = 1.5;

class ActionMovie : public Film {
private:
    unsigned actionIntensity; 

public:
    ActionMovie();

    ActionMovie(const MyString& title, double rating, unsigned length,
        unsigned year, unsigned room, const Date& date,
        const Hour& startTime, unsigned intensity);

    unsigned getIntensity() const;
    void setIntensity(unsigned newIntensity);

    double calculatePrice() const;
    void printInfo() const override;
};

