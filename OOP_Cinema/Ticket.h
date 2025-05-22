#pragma once
#include "Movie.h"
#include "RowAndCol.h"  // Separate the RowAndCol struct

// Forward declarations to break circular dependencies
class Room;
class Seat;

class Ticket
{
    Movie movie;
    const Room* room;  // Pointer to avoid ownership issues
    unsigned seatNumber;
    RowAndCol seatPosition;
    bool isReserved;

public:
    Ticket();
    Ticket(const Movie& movie, const Room& room, unsigned seatNumber, bool isReserved = false);

    // Setters
    void setMovie(const Movie& movie);
    void setRoom(const Room& room);
    void setSeatNumber(unsigned seatNumber);
    void setIsReserved(bool isReserved);

    // Getters
    const Movie& getMovie() const { return movie; }
    const Room& getRoom() const { return *room; }
    unsigned getSeatNumber() const { return seatNumber; }
    RowAndCol getSeatPosition() const { return seatPosition; }
    bool getIsReserved() const { return isReserved; }

    // Operations
    void reserveSeat() { isReserved = true; }
    void releaseSeat() { isReserved = false; }
    void printTicketInfo() const;

private:
    RowAndCol calculateSeatPosition(unsigned seatNumber) const;
};

