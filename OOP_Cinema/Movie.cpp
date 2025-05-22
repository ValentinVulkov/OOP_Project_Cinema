#include "Movie.h"
#include <iostream>
#include <stdexcept>

// Default constructor
Movie::Movie()
    : title(""), rating(0), length(0), year(0),
    genre(Genre::ActionMovie), room(0),
    date(Date(1, 1, 2000)), startTime(Hour(0, 0)),
    endTime(startTime + length) {}

// Parameterized constructor
Movie::Movie(const MyString& title, double rating, unsigned length,
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
const MyString& Movie::getTitle() const { return title; }
double Movie::getRating() const { return rating; }
unsigned Movie::getLength() const { return length; }
unsigned Movie::getYear() const { return year; }
Genre Movie::getGenre() const { return genre; }
unsigned Movie::getRoom() const { return room; }
const Date& Movie::getDate() const { return date; }
const Hour& Movie::getStartTime() const { return startTime; }
const Hour& Movie::getEndTime() const { return endTime; }

// Setters implementation
void Movie::setTitle(const MyString& newTitle) {
    if (newTitle == nullptr) {
        throw std::invalid_argument("Title cannot be empty");
    }
    title = newTitle;
}

void Movie::setRating(double newRating) {
    if (newRating < 0 || newRating > 10) {
        throw std::invalid_argument("Rating must be between 0 and 10");
    }
    rating = newRating;
}

void Movie::setLength(unsigned newLength) {
    if (newLength == 0) {
        throw std::invalid_argument("Length cannot be zero");
    }
    length = newLength;
    endTime = startTime + length;
}

void Movie::setYear(unsigned newYear) {
    year = newYear;
}

void Movie::setGenre(Genre newGenre) {
    genre = newGenre;
}

void Movie::setRoom(unsigned newRoom) {
    room = newRoom;
}

void Movie::setDate(const Date& newDate) {
    date = newDate;
}

void Movie::setStartTime(const Hour& newStartTime) {
    startTime = newStartTime;
    endTime = startTime + length;
}

void Movie::printInfo() const  {
    std::cout << "Title: " << title << "\n"
        << "Rating: " << rating << "\n"
        << "Length: " << length << " minutes\n"
        << "Year: " << year << "\n"
        << "Genre: " << static_cast<int>(genre) << "\n"
        << "Room: " << room << "\n"
        << "Date: " << date << "\n"
        << "Time: " << startTime << " - " << endTime << "\n";
}


