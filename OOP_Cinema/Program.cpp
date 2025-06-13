#include "Program.h"
#include "CinemaSystem.h"

Program::Program()
{
	srand(static_cast<unsigned int>(time(NULL)));
}

void Program::run()
{
    CinemaSystem& system = CinemaSystem::getInstance();
    std::cout << "Welcome to FMI Cinema System 2024-2025!\n";
    std::cout << "Please choose an action:\n\n";

    system.loadMovies();
    system.loadRooms();
    system.loadUsers();

    loop();
    save();
}

Program::~Program()
{
    this->save();
}

void Program::loop()
{
    while (true)
    {
        std::cout << "> ";
        MyString line;
        std::cin >> line;
    }
}

void Program::save()
{
    CinemaSystem& system = CinemaSystem::getInstance();
    system.saveMovies();
    system.saveRooms();
    system.saveUsers();
}
