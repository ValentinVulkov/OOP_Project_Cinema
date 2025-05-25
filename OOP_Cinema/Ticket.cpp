#include "Ticket.h"
#include "Room.h"
#include "Seat.h"
#include <iostream>

Ticket::Ticket() : movieId(), seat(), price() {}

Ticket::Ticket(unsigned movieId, const Seat& seat, double price){
	setSeat(seat);
	setPrice(price);
    setMovieId(movieId);
}

unsigned Ticket::getMovieId() const
{
	return movieId;
}

const Seat& Ticket::getSeat() const
{
	return seat;
}

double Ticket::getPrice() const
{
	return price;
}


void Ticket::setMovieId(unsigned movieId)
{
	this->movieId = movieId;

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

void Ticket::printTicketInfo() const {
    std::cout << "Ticket Information:\n";
    std::cout << "Movie Id: " << movieId << "\n";
    std::cout << "Seat: Row " << seat.getRow() << ", Column " << seat.getCol() << "\n";
    std::cout << "Price: " << price << " BGN\n";
}

void Ticket::writeToFile(std::ofstream& out) const {
	out.write(reinterpret_cast<const char*>(&movieId), sizeof(movieId));
	seat.writeToFile(out);
	out.write(reinterpret_cast<const char*>(&price), sizeof(price));
}

void Ticket::readFromFile(std::ifstream& in) {
	in.read(reinterpret_cast<char*>(&movieId), sizeof(movieId));
	seat.readFromFile(in);
	in.read(reinterpret_cast<char*>(&price), sizeof(price));
}
