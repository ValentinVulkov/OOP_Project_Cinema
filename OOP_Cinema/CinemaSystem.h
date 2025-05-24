#pragma once
#include "MyString.h"
#include "MyVector.hpp"
#include "User.h"
#include "Movie.h"
#include "ActionMovie.h"
#include "DocumentaryMovie.h"
#include "DramaMovie.h"
#include "Ticket.h"
#include "Room.h"
#include "Seat.h"
#include "Rating.h"
#include "fstream"
class CinemaSystem
{
	User* currentUser = nullptr;

	MyVector<User> users;
	MyVector<Movie*> movies;
	MyVector<Room> rooms;
	MyVector<Ticket> tickets;

	bool userExists(const User* user) const;
	size_t findBankByUsername(const MyString& username) const;

	void writeToFile() const;
	void readFromFile();

	void saveUsers() const;
	void saveBanks() const;
	void saveMovies() const;

	void loadUsers();
	void loadBanks();
	void loadMovies();

	CinemaSystem();
	~CinemaSystem();

public: 
	static CinemaSystem& getInstance();

	CinemaSystem(const CinemaSystem& other) = delete;
	CinemaSystem& operator=(const CinemaSystem& other) = delete;

	void addMovie(const Movie& movie);

	void addUser(const MyString& username, const MyString& password, bool isAdmin, MyVector<Ticket>& tickets, MyVector<Movie>& watchedMovies);

	void addRoom(const Room& room);


};

