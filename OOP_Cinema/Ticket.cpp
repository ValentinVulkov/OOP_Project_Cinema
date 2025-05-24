#include "Ticket.h"
#include "Room.h"
#include "Seat.h"
#include <iostream>

Ticket::Ticket() : movie(), seat() {}

Ticket::Ticket(const Movie& movie, const Seat& seat)
{
	setMovie(movie);
	setSeat(seat);
}

const Movie& Ticket::getMovie() const
{
	return movie;
}

const Seat& Ticket::getSeat() const
{
	return seat;
}

void Ticket::setMovie(const Movie& movie)
{
	this->movie = movie;
}

void Ticket::setSeat(const Seat& seat)
{
	this->seat = seat;

}

void Ticket::printTicketInfo() const
{
	std::cout << "Ticket Information:" << std::endl;
	std::cout << "Movie: " << movie.getTitle() << std::endl;
	std::cout << "Seat: Row " << seat.getRow() << ", Column " << seat.getCol() << std::endl;
	std::cout << "Reserved: " << (seat.getReserved() ? "Yes" : "No") << std::endl;
}
