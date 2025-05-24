#include "Room.h"

Room::Room() : ID(RoomManager::assignID()), rows(0), cols(0) {}

Room::Room(unsigned rows, unsigned cols)
    : ID(RoomManager::assignID()), rows(rows), cols(cols)
{
    // Initialize each row
    for (unsigned i = 0; i < rows; ++i) {
        MyVector<Seat> currentRow;  // Create a new row

        // Fill the row with seats
        for (unsigned j = 0; j < cols; ++j) {
            currentRow.push_back(Seat());  // Add each seat
        }

        seats.push_back(currentRow);  // Add the completed row
    }
}

// Destructor
Room::~Room() {
    if (ID != 0) {  // Only release valid IDs
        RoomManager::releaseID(ID);
    }
}

// Getters
unsigned Room::getID() const
{
	return ID;
}
unsigned Room::getRows() const
{
	return rows;
}
unsigned Room::getCols() const
{
	return cols;
}
const MyVector<MyVector<Seat>>& Room::getSeats() const
{
    return seats;
}

// Setters
void Room::setRows(unsigned r) {
    if (r > rows) {
        // Add new rows
        for (unsigned i = rows; i < r; ++i) {
            MyVector<Seat> newRow;
            for (unsigned j = 0; j < cols; ++j) {
                newRow.push_back(Seat());
            }
            seats.push_back(newRow);
        }
    }
    else if (r < rows) {
        // Remove excess rows
        for (unsigned i = rows; i > r; --i) {
            seats.pop_back();
        }
    }
    rows = r;
}

void Room::setCols(unsigned c) {
    if (c > cols) {
        // Expand existing rows
        for (unsigned i = 0; i < rows; ++i) {
            for (unsigned j = cols; j < c; ++j) {
                seats[i].push_back(Seat());
            }
        }
    }
    else if (c < cols) {
        // Shrink existing rows
        for (unsigned i = 0; i < rows; ++i) {
            for (unsigned j = cols; j > c; --j) {
                seats[i].pop_back();
            }
        }
    }
    cols = c;
}

// Seat access
Seat& Room::getSeat(unsigned row, unsigned col) {
    if (row >= rows || col >= cols) {
        throw std::out_of_range("Seat position out of range");
    }
    return seats[row][col];
}

const Seat& Room::getSeat(unsigned row, unsigned col) const {
    if (row >= rows || col >= cols) {
        throw std::out_of_range("Seat position out of range");
    }
    return seats[row][col];
}

void Room::writeToFile(std::ofstream& out) const {
    if (!out.good()) throw std::runtime_error("Room output stream error");

    const char marker = 'R';
    out.write(&marker, 1);
    out.write(reinterpret_cast<const char*>(&ID), sizeof(ID));
    out.write(reinterpret_cast<const char*>(&rows), sizeof(rows));
    out.write(reinterpret_cast<const char*>(&cols), sizeof(cols));

    // Write seats grid
    for (unsigned i = 0; i < rows; ++i) {
        for (unsigned j = 0; j < cols; ++j) {
            seats[i][j].writeToFile(out);
        }
    }
}

void Room::readFromFile(std::ifstream& in) {
    if (!in.good()) throw std::runtime_error("Room input stream error");

    char marker;
    in.read(&marker, 1);
    if (marker != 'R') throw std::runtime_error("Invalid Room data marker");

    in.read(reinterpret_cast<char*>(&ID), sizeof(ID));
    in.read(reinterpret_cast<char*>(&rows), sizeof(rows));
    in.read(reinterpret_cast<char*>(&cols), sizeof(cols));

    // Rebuild seats grid
    seats = MyVector<MyVector<Seat>>(rows, MyVector<Seat>(cols));
    for (unsigned i = 0; i < rows; ++i) {
        for (unsigned j = 0; j < cols; ++j) {
            seats[i][j].readFromFile(in);
        }
    }
}