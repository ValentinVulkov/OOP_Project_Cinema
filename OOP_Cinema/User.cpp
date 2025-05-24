#include "User.h"

User::User() : username(""), password(""), tickets(0), watchedMovies(0), balance(0){}

User::User(const MyString& username, const MyString& password, bool isAdmin, MyVector<Ticket> tickets, MyVector<Movie> watchedMovies, unsigned balance)
{
	setUsername(username);
	setPassword(password);
	setTickets(tickets);
	setWatchedMovies(watchedMovies);
	setBalance(balance);
	setAdmin(isAdmin);
}

const MyString& User::getUsername() const
{
	return username;
}

const MyString& User::getPassword() const
{
	return password;
}

unsigned User::getBalance() const
{
	return balance;
}

const MyVector<Ticket>& User::getTickets() const
{
	return tickets;
}

const MyVector<Movie>& User::getWatchedMovies() const
{
	return watchedMovies;
}

const bool User::getIsAdmin() const
{
	return isAdmin;
}

void User::setUsername(const MyString& username)
{
	if (username.getSize() < 3)
	{
		throw std::invalid_argument("Username must be at least 3 characters long.");
	}
}

void User::setPassword(const MyString& password)
{
	if (password.getSize() < 6)
	{
		throw std::invalid_argument("Password must be at least 6 characters long.");
	}
}

void User::setBalance(unsigned balance)
{
	this->balance = balance;
}

void User::setTickets(const MyVector<Ticket>& tickets)
{
	this->tickets = tickets;
}

void User::setWatchedMovies(const MyVector<Movie>& watchedMovies)
{
	this->watchedMovies = watchedMovies;
}

void User::setAdmin(bool isAdmin)
{
	this->isAdmin = isAdmin;
}

void User::addTicket(const Ticket& ticket)
{
	//...
}

void User::addWatchedMovie(const Movie& movie)
{
	//...
}
