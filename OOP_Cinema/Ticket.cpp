#include "Ticket.h"
#include "Room.h"  // Now safe to include after forward declaration
#include <iostream>

Ticket::Ticket()
    : movie(), room(nullptr), seatNumber(0),
    seatPosition({ 0, 0 }), isReserved(false) {}

Ticket::Ticket(const Movie& movie, const Room& room,
    unsigned seatNumber, bool isReserved)
    : movie(movie), room(&room), seatNumber(seatNumber),
    isReserved(isReserved)
{
    seatPosition = calculateSeatPosition(seatNumber);
}

void Ticket::setMovie(const Movie& movie) {
    this->movie = movie;
}

void Ticket::setRoom(const Room& room) {
    this->room = &room;
    // Recalculate position when room changes
    seatPosition = calculateSeatPosition(seatNumber);
}

void Ticket::setSeatNumber(unsigned seatNumber) {
    this->seatNumber = seatNumber;
    seatPosition = calculateSeatPosition(seatNumber);
}

void Ticket::setIsReserved(bool isReserved) {
    this->isReserved = isReserved;
}

RowAndCol Ticket::calculateSeatPosition(unsigned seatNumber) const {
    if (!room) return { 0, 0 };  // Handle null room case

    unsigned cols = room->getCols();
    if (cols == 0) return { 0, 0 };  // Prevent division by zero

    unsigned row = (seatNumber - 1) / cols;  // 1-based to 0-based
    unsigned col = (seatNumber - 1) % cols;
    return { row, col };
}

void Ticket::printTicketInfo() const {
    std::cout << "Movie: " << movie.getTitle() << '\n';
    if (room) {
        std::cout << "Room: " << room->getID() << '\n';
    }
    else {
        std::cout << "Room: (none)\n";
    }
    std::cout << "Seat Number: " << seatNumber << '\n'
        << "Seat Position: Row " << seatPosition.row + 1  // Show as 1-based
        << ", Column " << seatPosition.col + 1 << '\n'
        << "Status: " << (isReserved ? "Reserved" : "Available") << '\n';
}