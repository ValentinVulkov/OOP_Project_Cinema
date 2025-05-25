#include "Room.h"

unsigned Room::nextId = 1;

Room::Room() : Id(nextId++), rows(0), cols(0) {}

Room::Room(unsigned rows, unsigned cols)
    : Id(nextId++), rows(rows), cols(cols)
{
    seats = MyVector<MyVector<Seat>>(rows, MyVector<Seat>(cols));


    //for (unsigned i = 0; i < rows; ++i) {
    //    MyVector<Seat> currentRow;  

    //    
    //    for (unsigned j = 0; j < cols; ++j) {
    //        currentRow.push_back(Seat()); 
    //    }

    //    seats.push_back(currentRow); 
    //}
}


Room::~Room() = default;

unsigned Room::getID() const
{
	return Id;
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

void Room::writeToTextFile(std::ofstream& out) const {
    out << Id << ' ' << rows << ' ' << cols << '\n';

    // Write seat matrix
    for (unsigned i = 0; i < rows; ++i) {
        for (unsigned j = 0; j < cols; ++j) {
            out << (seats[i][j].getReserved() ? '1' : '0');
            if (j < cols - 1) out << ' ';
        }
        out << '\n';
    }
}

void Room::readFromTextFile(std::ifstream& in) {
    // Read basic room info
    in >> Id;
    setNextIdIfLarger(Id);
    in >> rows >> cols;
    in.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear to end of line

    // Initialize seats vector
    seats = MyVector<MyVector<Seat>>(rows, MyVector<Seat>(cols));

    // Read seat statuses
    for (unsigned i = 0; i < rows; ++i) {
        for (unsigned j = 0; j < cols; ++j) {
            int status;
            in >> status;
            seats[i][j].setReserved(status == 1);
        }
        in.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear to end of line after each row
    }
}

void Room::setNextIdIfLarger(unsigned testId) {
    if (testId >= nextId) {
        nextId = testId + 1;
    }
}

void Room::printInfo() const
{
	std::cout << "Room Information:" << std::endl;
	std::cout << "Rows: " << rows << std::endl;
	std::cout << "Columns: " << cols << std::endl;
	std::cout << "Room ID: " << Id << std::endl;
}
