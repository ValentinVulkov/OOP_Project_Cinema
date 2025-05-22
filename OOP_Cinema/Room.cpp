#include "Room.h"

Room::Room(unsigned numRows, unsigned numCols)
    : ID(RoomManager::assignID()),
    rows(numRows),
    cols(numCols) {
    initializeSeats();
}

Room::~Room() {
    if (ID != 0) {  // Only release if not already closed
        RoomManager::releaseID(ID);
    }
    cleanupSeats();
}

Room::Room(Room&& other) noexcept
    : ID(other.ID),
    rows(other.rows),
    cols(other.cols),
    seats(std::move(other.seats)) {
    // Invalidate the moved-from object
    other.ID = 0;
    other.rows = 0;
    other.cols = 0;
}

Room& Room::operator=(Room&& other) noexcept {
    if (this != &other) {
        // Release current resources
        if (ID != 0) {
            RoomManager::releaseID(ID);
        }
        cleanupSeats();

        // Transfer ownership
        ID = other.ID;
        rows = other.rows;
        cols = other.cols;
        seats = std::move(other.seats);

        // Invalidate the moved-from object
        other.ID = 0;
        other.rows = 0;
        other.cols = 0;
    }
    return *this;
}


void Room::initializeSeats() {
    // Initialize rows using constructor
    seats = MyVector<MyVector<Seat*>>(rows);

    for (unsigned r = 0; r < rows; r++) {
        // Initialize columns for each row
        seats[r] = MyVector<Seat*>(cols);

        for (unsigned c = 0; c < cols; c++) {
            seats[r][c] = new Seat(this, r, c);
        }
    }
}

void Room::cleanupSeats() {
    for (unsigned r = 0; r < seats.getSize(); r++) {
        for (unsigned c = 0; c < seats[r].getSize(); c++) {
            delete seats[r][c];
        }
    }
}

Seat* Room::getSeat(unsigned row, unsigned col) const {
    if (row >= rows || col >= cols) {
        return nullptr;
    }
    return seats[row][col];
}

void Room::close() {
    if (ID != 0) {
        RoomManager::releaseID(ID);
        ID = 0;  // Mark as closed
    }
}
