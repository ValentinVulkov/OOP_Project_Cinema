#pragma once
#include "Seat.h"

class Movie; // Forward declaration

class Ticket {
	unsigned movieId;  // Store ID instead of pointer
	Seat seat;
	double price;

public:
	Ticket();
	Ticket(unsigned movieId, const Seat& seat, double price);

	unsigned getMovieId() const;
	const Seat& getSeat() const;
	double getPrice() const;


	void setMovieId(unsigned movieId);
	void setSeat(const Seat& seat);
	void setPrice(double price);

	void printTicketInfo() const;
	~Ticket() = default;

	void writeToFile(std::ofstream& out) const;
	void readFromFile(std::ifstream& in);


};