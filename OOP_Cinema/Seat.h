#pragma once
#include <fstream>
#include <stdexcept>

// Forward declaration instead of full Room include
class Room;

class Seat
{
private:
    unsigned row;
    unsigned col;
    bool isReserved;

public:
    Seat();
    Seat(unsigned row, unsigned col, bool isReserved);
	void setRow(unsigned row);
	void setCol(unsigned col);
	void setReserved(bool isReserved);

	unsigned getRow() const;
	unsigned getCol() const;
	bool getReserved() const;
	~Seat() = default;

	void writeToTextFile(std::ofstream& out) const;
	void readFromTextFile(std::ifstream& in);

};