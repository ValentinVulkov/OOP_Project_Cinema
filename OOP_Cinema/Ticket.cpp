#include "Ticket.h"
#include "Room.h"
#include "Seat.h"
#include <iostream>

Ticket::Ticket() : movie(), seat() {}

Ticket::Ticket(const Movie& movie, const Seat& seat, double price)
{
	setMovie(movie);
	setSeat(seat);
	setPrice(price);
}

const Movie& Ticket::getMovie() const
{
	return movie;
}

const Seat& Ticket::getSeat() const
{
	return seat;
}

double Ticket::getPrice() const
{
	return price;
}

void Ticket::setMovie(const Movie& movie)
{
	this->movie = movie;
}

void Ticket::setSeat(const Seat& seat)
{
	this->seat = seat;

}

void Ticket::setPrice(double price)
{
	if (price < 0) {
		throw std::invalid_argument("Price cannot be negative");
	}
	this->price = price;
}

void Ticket::printTicketInfo() const
{
	std::cout << "Ticket Information:" << std::endl;
	std::cout << "Movie: " << movie.getTitle() << std::endl;
	std::cout << "Seat: Row " << seat.getRow() << ", Column " << seat.getCol() << std::endl;
	std::cout << "Reserved: " << (seat.getReserved() ? "Yes" : "No") << std::endl;
}

void Ticket::writeToFile(std::ofstream& out) const {

    movie.writeToFile(out);

    seat.writeToFile(out);

    out.write(reinterpret_cast<const char*>(&price), sizeof(price));
}

void Ticket::readFromFile(std::ifstream& in) {
    // 1. Read Movie
    movie.readFromFile(in);

    // 2. Read Seat
    seat.readFromFile(in);

    // 3. Read primitive members
    in.read(reinterpret_cast<char*>(&price), sizeof(price));
}
