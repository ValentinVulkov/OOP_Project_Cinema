#pragma once
#include "MyVector.hpp"
#include "Seat.h"
#include "RoomManager.h"


 
class Room {
private:
    unsigned ID;
    unsigned rows;
    unsigned cols;
    MyVector<MyVector<Seat>> seats;

public:
    Room();
    explicit Room(unsigned rows, unsigned cols);

    unsigned getID() const;
    unsigned getRows() const;
    unsigned getCols() const;
    const MyVector<MyVector<Seat>>& getSeats() const;

    void setRows(unsigned rows);
    void setCols(unsigned cols);

    Seat& getSeat(unsigned row, unsigned col);
    const Seat& getSeat(unsigned row, unsigned col) const;
    ~Room();

    void writeToFile(std::ofstream& out) const;
    void readFromFile(std::ifstream& in);
};