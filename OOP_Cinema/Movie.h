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
    unsigned Id;
	static unsigned nextId;
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

	explicit Movie(unsigned Id, const MyString& title, unsigned length,
		unsigned year, Genre genre, Room room,
		const Date& date, const Hour& startTime);  // second constructor if manually setting Id's is manditory

    // Getters
	unsigned getId() const;
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

    void writeToFile(std::ofstream& out) const;
    void readFromFile(std::ifstream& in);
};
