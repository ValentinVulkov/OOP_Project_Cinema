#pragma once
#include "MyString.h"
#include "MyVector.hpp"
#include "Movie.h"
#include "Ticket.h"
#include "HelpFunc.h"

class User
{
protected:
	MyString username;
	MyString password;
	bool isAdmin;
	MyVector<Ticket> tickets;
	MyVector<unsigned> watchedMovieIds;
	double balance;

public:
	User();
	User(const MyString& username, const MyString& password, bool isAdmin, MyVector<Ticket> tickets, MyVector<unsigned> watchedMovieIds, double balance);

	const MyString& getUsername() const;
	const MyString& getPassword() const;
	double getBalance() const;
	const MyVector<Ticket> getTickets() const;
	const MyVector<unsigned> getWatchedMovieIds() const;
	const bool getIsAdmin() const;

	void setUsername(const MyString& username);
	void setPassword(const MyString& password);
	void setBalance(double balance);
	void setTickets(const MyVector<Ticket>& tickets);
	void setWatchedMovieIds(const MyVector<unsigned>& watchedMovieIds);
	void setAdmin(bool isAdmin);
	~User() = default;


	void writeToTextFile(std::ofstream& ofs) const;
	void readFromTextFile(std::ifstream& ifs);

	void printInfo() const;
};

