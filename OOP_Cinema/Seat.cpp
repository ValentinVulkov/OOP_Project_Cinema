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

void Seat::writeToFile(std::ofstream& out) const {
    if (!out.good()) throw std::runtime_error("Seat output stream error");

    const char marker = 'S';
    out.write(&marker, 1);
    out.write(reinterpret_cast<const char*>(&row), sizeof(row));
    out.write(reinterpret_cast<const char*>(&col), sizeof(col));
    out.write(reinterpret_cast<const char*>(&isReserved), sizeof(isReserved));
}

void Seat::readFromFile(std::ifstream& in) {
    if (!in.good()) throw std::runtime_error("Seat input stream error");

    char marker;
    in.read(&marker, 1);
    if (marker != 'S') throw std::runtime_error("Invalid Seat data marker");

    in.read(reinterpret_cast<char*>(&row), sizeof(row));
    in.read(reinterpret_cast<char*>(&col), sizeof(col));
    in.read(reinterpret_cast<char*>(&isReserved), sizeof(isReserved));

    // Basic validation
    if (row > 100 || col > 100) {  // Assuming max 100 rows/cols
        throw std::runtime_error("Invalid seat position");
    }
}