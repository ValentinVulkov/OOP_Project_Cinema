#include "Seat.h"

Seat::Seat() : row(0), col(0), isReserved(false){}

Seat::Seat(unsigned row, unsigned col, bool isReserved)
{
	setRow(row);
    setCol(col);
	setReserved(isReserved);
}

void Seat::setRow(unsigned row)
{
	this->row = row;
}

void Seat::setCol(unsigned col)
{
	this->col = col;
}

void Seat::setReserved(bool isReserved)
{
	this->isReserved = isReserved;
}

unsigned Seat::getRow() const
{
    return row;
}

unsigned Seat::getCol() const
{
    return col;
}

bool Seat::getReserved() const
{
    return isReserved;
}

void Seat::writeToTextFile(std::ofstream& out) const {
    out << row << " " << col << " " << isReserved << "\n";
}

void Seat::readFromTextFile(std::ifstream& in) {
    in >> isReserved;
}