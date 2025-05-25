#include "CinemaSystemLauncher.h"
#include "CommandFactory.h"

void CinemaSystemLauncher::run()
{
	CinemaSystem& system = CinemaSystem::getInstance();
	MyString cmd = "";

	while (true)
	{
		std::cout << "Enter you command here>> ";
		std::cin >> cmd;

		if (cmd == "stop")
		{
			break;
		}

		polymorphic_ptr<Command> command = CommandFactory::createCommand(cmd);

		if (!command.get())
		{
			std::cout << "Invalid command!" << std::endl;
		}
		else
		{
			command->execute(&system);
		}

		std::cout << std::endl << std::endl;
	}
}