#include "CinemaSystemLauncher.h"
#include "CommandHandler.h"
#include <iostream>
#include <string>

void CinemaSystemLauncher::run()
{
    CinemaSystem& system = CinemaSystem::getInstance();
    CinemaCommandHandler commandHandler(system);

    // Load existing data
    try {
        system.loadUsers();
        system.loadRooms();
        system.loadMovies();
        std::cout << "Cinema system data loaded successfully." << std::endl;
    }
    catch (const std::exception& e) {
        std::cout << "Warning: Could not load some data files: " << e.what() << std::endl;
        std::cout << "Starting with empty system." << std::endl;
    }

    std::cout << "=== Welcome to the Cinema Management System ===" << std::endl;
    std::cout << "Type 'help' for available commands or 'quit' to exit." << std::endl;

    std::string commandLine;
    while (true) {
        std::cout << "\n> ";
        std::getline(std::cin, commandLine);

        if (commandLine.empty()) {
            continue;
        }

        // Convert std::string to MyString for compatibility
        MyString myCommandLine(commandLine.c_str());
        commandHandler.dispatch(myCommandLine);

        // Check if user wants to quit (handled in command handler via exit())
    }
}