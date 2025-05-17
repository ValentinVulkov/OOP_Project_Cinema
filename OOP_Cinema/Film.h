#pragma once
#include "MyString.h"
#include "Date.h"
#include "Hour.h"

enum class Genre {
    ActionMovie,
    DramaMovie,
    DocumentaryMovie
};

class Film {
private:
    MyString title;
    double rating;
    unsigned length; // in minutes
    unsigned year;
    Genre genre;
    unsigned room;
    Date date;
    Hour startTime;
    Hour endTime;

public:

    Film();
    Film(const MyString& title, double rating, unsigned length,
        unsigned year, Genre genre, unsigned room,
        const Date& date, const Hour& startTime);

    // Getters
    const MyString& getTitle() const;
    double getRating() const;
    unsigned getLength() const;
    unsigned getYear() const;
    Genre getGenre() const;
    unsigned getRoom() const;
    const Date& getDate() const;
    const Hour& getStartTime() const;
    const Hour& getEndTime() const;

    // Setters
    void setTitle(const MyString& newTitle);
    void setRating(double newRating);
    void setLength(unsigned newLength);
    void setYear(unsigned newYear);
    void setGenre(Genre newGenre);
    void setRoom(unsigned newRoom);
    void setDate(const Date& newDate);
    void setStartTime(const Hour& newStartTime);

    virtual void printInfo() const ;
};
