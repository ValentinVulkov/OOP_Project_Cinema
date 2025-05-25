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
	/*system.loadRooms();
	std::cout << "Room count" << system.getRoomsCount() << '\n';
	system.rooms[0].printInfo();
	std::cout << '\n';
	std::cout << system.rooms[0].getSeat(0, 0).getReserved() << '\n';
	system.rooms[0].getSeat(0, 0).setReserved(1);
	std::cout << system.rooms[0].getSeat(0, 0).getReserved() << '\n';

	system.saveRooms();*/

	system.loadMovies();
	system.movies[1]->printInfo();
	std::cout << "Movie count: " << system.getMoviesCount() << '\n';
	

	/*std::ifstream in("DateTest.txt");
	Date date;
	unsigned id;
	in >> id;
	date.readFromTextFile(in);
	std::cout << date;*/


	return 0;
}