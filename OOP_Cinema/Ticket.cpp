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

void Ticket::writeToTextFile(std::ofstream& out) const {
    if (!out.is_open()) {
        throw std::runtime_error("Output file stream is not open");
    }

    out << movieId << " ";          // Записване на movieId
    out << seat.getRow() << " ";    // Записване на ред
    out << seat.getCol() << " ";    // Записване на колона
    out << price << "\n";           // Записване на цена с нов ред
}

void Ticket::readFromTextFile(std::ifstream& in) {
    if (!in.is_open()) {
        throw std::runtime_error("Input file stream is not open");
    }

    unsigned row, col;
    in >> movieId >> row >> col >> price;

    seat.setRow(row);      // Задаване на ред
    seat.setCol(col);      // Задаване на колона
    in.ignore();           // Прескачане на нов ред
}
