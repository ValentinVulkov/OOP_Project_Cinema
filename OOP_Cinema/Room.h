#pragma once
#include "MyVector.hpp"
#include "Seat.h"
#include <iostream>


 
class Room {
private:
    unsigned Id;
	static unsigned nextId;
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

    void writeToTextFile(std::ofstream& out) const;
    void readFromTextFile(std::ifstream& in);

    static void setNextIdIfLarger(unsigned testId);

    void printInfo() const;
};