#include "CinemaSystem.h"

bool CinemaSystem::userExists(const User* user) const
{
	for (size_t i = 0; i < users.getSize(); i++)
	{
		if (user->getUsername() == users[i].getUsername())
		{
			return true;
		}
	}
	return false;
}

size_t CinemaSystem::findBankByUsername(const MyString& username) const
{
	for (size_t i = 0; i < users.getSize(); i++)
	{
		if (users[i].getUsername() == username)
		{
			return i;
		}
	}
	return users.getSize();
}

void CinemaSystem::saveMovies() const
{
	// Implementation for saving movies to a file or database

	std::ofstream ofs("users.txt");

	if (!ofs.is_open())
	{
		return;
	}
	size_t size = users.getSize();
	ofs.write((const char*)&(size), sizeof(size_t));

	for (size_t i = 0; i < size; i++)
	{
		users[i].writeToFile(ofs);
	}

	ofs.close();
}

void CinemaSystem::loadMovies()
{
	// Implementation for loading movies from a file or database

}
