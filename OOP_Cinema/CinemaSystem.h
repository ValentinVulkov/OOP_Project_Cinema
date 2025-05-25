#pragma once
#include "MyString.h"
#include "MyVector.hpp"
#include "polymorphic_ptr.hpp"
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
public:

	User* currentUser = nullptr;

	MyVector<User> users;
	MyVector<Movie*> movies;
	MyVector<Room> rooms;
	MyVector<Ticket> tickets;

	void saveUsers() const;
	void saveRooms() const;
	void saveMovies() const;

	void loadUsers();
	void loadRooms();
	void loadMovies();

	void Login();
	void setCurrentUser(User* user);
	User* getCurrentUser() const;

	bool removeRoomById(unsigned id);

	CinemaSystem();
	~CinemaSystem();



public: 
	static CinemaSystem& getInstance();

	CinemaSystem(const CinemaSystem& other) = delete;
	CinemaSystem& operator=(const CinemaSystem& other) = delete;


	size_t getMoviesCount() const;
	Movie* getMovieByIndex(size_t index);
	size_t getRoomsCount() const;
	const Room& getRoomByIndex(size_t index) const;
	size_t getUsersCount() const;

	bool userExists(const User* user) const;
	User* findUserByUsername(const MyString& username);
	const User* findUserByUsername(const MyString& username) const;
};

