#pragma once
#include "MyVector.hpp"
#include "Seat.h"
#include "RoomManager.h"

//Setters not implemented

 
class Room {
private:
    unsigned ID;
    unsigned rows;
    unsigned cols;
    MyVector<MyVector<Seat*>> seats;  // 2D vector of seats

public:
    Room(unsigned numRows, unsigned numCols);
    ~Room();

    // Delete copy operations
    Room(const Room&) = delete;
    Room& operator=(const Room&) = delete;

    // Move operations
    Room(Room&& other) noexcept;
    Room& operator=(Room&& other) noexcept;

    // Accessors
    unsigned getID() const { return ID; }
    unsigned getRows() const { return rows; }
    unsigned getCols() const { return cols; }
    unsigned getTotalSeats() const { return rows * cols; }

    Seat* getSeat(unsigned row, unsigned col) const;
    void close();

private:
    void initializeSeats();
    void cleanupSeats();
};