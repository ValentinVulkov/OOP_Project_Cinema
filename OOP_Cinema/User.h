#pragma once
#include "MyString.h"
#include "MyVector.hpp"
#include "Movie.h"
#include "Ticket.h"
class User
{
protected:
	MyString username;
	MyString password;
	bool isAdmin;
	MyVector<Ticket> tickets;
	MyVector<Movie> watchedMovies;
	unsigned balance;

public:
	User();
	User(const MyString& username, const MyString& password, bool isAdmin, MyVector<Ticket> tickets, MyVector<Movie> watchedMovies, unsigned balance = 0);

	const MyString& getUsername() const;
	const MyString& getPassword() const;
	unsigned getBalance() const;
	const MyVector<Ticket>& getTickets() const;
	const MyVector<Movie>& getWatchedMovies() const;
	const bool getIsAdmin() const;

	void setUsername(const MyString& username);
	void setPassword(const MyString& password);
	void setBalance(unsigned balance);
	void setTickets(const MyVector<Ticket>& tickets);
	void setWatchedMovies(const MyVector<Movie>& watchedMovies);
	void setAdmin(bool isAdmin);
	~User() = default;


	void addTicket(const Ticket& ticket);
	void addWatchedMovie(const Movie& movie);
	
	void writeToFile(std::ofstream& ofs) const;
};

