#include "Film.h"
#include <iostream>
#include <stdexcept>

// Default constructor
Film::Film()
    : title(""), rating(0), length(0), year(0),
    genre(Genre::ActionMovie), room(0),
    date(Date(1, 1, 2000)), startTime(Hour(0, 0)),
    endTime(startTime + length) {}

// Parameterized constructor
Film::Film(const MyString& title, double rating, unsigned length,
    unsigned year, Genre genre, unsigned room,
    const Date& date, const Hour& startTime)
    : title(title), rating(rating), length(length),
    year(year), genre(genre), room(room),
    date(date), startTime(startTime),
    endTime(startTime + length) {

    if (rating < 0 || rating > 10) {
        throw std::invalid_argument("Rating must be between 0 and 10");
    }
    if (length == 0) {
        throw std::invalid_argument("Length cannot be zero");
    }
}

// Getters implementation
const MyString& Film::getTitle() const { return title; }
double Film::getRating() const { return rating; }
unsigned Film::getLength() const { return length; }
unsigned Film::getYear() const { return year; }
Genre Film::getGenre() const { return genre; }
unsigned Film::getRoom() const { return room; }
const Date& Film::getDate() const { return date; }
const Hour& Film::getStartTime() const { return startTime; }
const Hour& Film::getEndTime() const { return endTime; }

// Setters implementation
void Film::setTitle(const MyString& newTitle) {
    if (newTitle == nullptr) {
        throw std::invalid_argument("Title cannot be empty");
    }
    title = newTitle;
}

void Film::setRating(double newRating) {
    if (newRating < 0 || newRating > 10) {
        throw std::invalid_argument("Rating must be between 0 and 10");
    }
    rating = newRating;
}

void Film::setLength(unsigned newLength) {
    if (newLength == 0) {
        throw std::invalid_argument("Length cannot be zero");
    }
    length = newLength;
    endTime = startTime + length;
}

void Film::setYear(unsigned newYear) {
    year = newYear;
}

void Film::setGenre(Genre newGenre) {
    genre = newGenre;
}

void Film::setRoom(unsigned newRoom) {
    room = newRoom;
}

void Film::setDate(const Date& newDate) {
    date = newDate;
}

void Film::setStartTime(const Hour& newStartTime) {
    startTime = newStartTime;
    endTime = startTime + length;
}

void Film::printInfo() const  {
    std::cout << "Title: " << title << "\n"
        << "Rating: " << rating << "\n"
        << "Length: " << length << " minutes\n"
        << "Year: " << year << "\n"
        << "Genre: " << static_cast<int>(genre) << "\n"
        << "Room: " << room << "\n"
        << "Date: " << date << "\n"
        << "Time: " << startTime << " - " << endTime << "\n";
}


