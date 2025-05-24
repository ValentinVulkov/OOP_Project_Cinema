#pragma once
#include "MyString.h"
#include "Date.h"
#include "Hour.h"
#include "Rating.h"
#include "Room.h"

enum class Genre {
    ActionMovie,
    DramaMovie,
    DocumentaryMovie
};

class Movie {
private:
    MyString title;
    unsigned length; // in minutes
    unsigned year;
    Genre genre;
    Room room;          
    Date date;
    Hour startTime;
    Hour endTime;
	MyVector<Rating> ratings; // List of ratings for the movie
	double averageRating; // Average rating of the movie

public:

    Movie();
    Movie(const MyString& title, unsigned length,
        unsigned year, Genre genre, Room room,
        const Date& date, const Hour& startTime, MyVector<Rating> ratings);

    // Getters
    const MyString& getTitle() const;
    unsigned getLength() const;
    unsigned getYear() const;
    Genre getGenre() const;
    Room getRoom() const;
    const Date& getDate() const;
    const Hour& getStartTime() const;
    const Hour& getEndTime() const;
	const MyVector<Rating>& getRatings() const;
	const double getAverageRating() const;

    // Setters
    void setTitle(const MyString& newTitle);
    void setLength(unsigned newLength);
    void setYear(unsigned newYear);
    void setGenre(Genre newGenre);
    void setRoom(Room newRoom);
    void setDate(const Date& newDate);
    void setStartTime(const Hour& newStartTime);
	void setRatings(const MyVector<Rating> ratings);

	double calculateAverageRating(const MyVector<Rating>& ratings) const;

    void addRating(const Rating& rating);

    virtual void printInfo() const ;
	virtual ~Movie() = default;
};
