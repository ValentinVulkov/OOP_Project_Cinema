#include <iostream>
#include <fstream>
#include <iostream>
#include "MyString.h"
#include "Login.h"
#include "Hour.h"
#include "CinemaSystem.h"
#include "CinemaSystemLauncher.h"



int main()
{
	CinemaSystem& system = CinemaSystem::getInstance();
	


	system.loadMovies();
	system.saveMovies();

	system.loadRooms();
	system.saveRooms();

	system.loadUsers();
	system.users[0].setUsername("gash");
	system.users[0].printInfo();
	system.saveUsers();


	return 0;
}