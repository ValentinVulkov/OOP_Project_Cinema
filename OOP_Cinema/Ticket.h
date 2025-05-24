#pragma once
#include "Movie.h"
#include "Seat.h"

// Forward declarations
class Room;
class Seat;

class Ticket {
    Movie movie;
    Seat seat;

public:
	Ticket();
	Ticket(const Movie& movie, const Seat& seat);

	const Movie& getMovie() const;
	const Seat& getSeat() const;

	void setMovie(const Movie& movie);
	void setSeat(const Seat& seat);

	void printTicketInfo() const;
	~Ticket() = default;
};