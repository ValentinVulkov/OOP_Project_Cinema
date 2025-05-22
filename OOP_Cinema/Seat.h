#pragma once


// Forward declaration instead of full Room include
class Room;

class Seat
{
private:
    Room* room;  // Change to pointer to break circular dependency
    unsigned row;
    unsigned col;
    bool isReserved;

public:
    // Add proper constructor
    Seat(Room* roomPtr, unsigned rowNum, unsigned colNum)
        : room(roomPtr), row(rowNum), col(colNum), isReserved(false) {}

    // Add getters
    unsigned getRow() const { return row; }
    unsigned getCol() const { return col; }
    bool getReserved() const { return isReserved; }

    // Add seat functionality
    void reserve() { isReserved = true; }
    void release() { isReserved = false; }
};
