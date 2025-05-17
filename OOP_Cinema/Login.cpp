#include "Login.h"
#include "MyString.h"
#include <fstream>
#include <iostream>
#include <stdexcept>

int category=0;

void accountOption() // starting menu
{
	std::cout << "Welcome, enter 1 to login into an excisting account, or enter 2 to register a new accout" << '\n';
	chooseOption();
}

void chooseOption()
{
	int chosenAccountOption = 0;
	std::cin >> chosenAccountOption;
	if (chosenAccountOption != 1 && chosenAccountOption != 2)
	{
		std::cout << "Not an avalable option, please try again.";
		accountOption();
	}
	else if (chosenAccountOption == 1)
	{
		loginAccount();

	}
	else
	{
		registerAccount();
	}
}

int loginAccount()  // Връща 1 за норм, 2 за админ, -1 за неуспешо
{
	std::ifstream ifs("Accounts.txt");
	if (!ifs.is_open())
	{
		throw std::runtime_error("Failed to open Accounts.txt");
	}

	MyString enteredUsername;
	MyString enteredPassword;
	std::cout << "Enter username: " << '\n';
	std::cin >> enteredUsername;
	std::cout << "Enter passowrd: " << '\n';
	std::cin >> enteredPassword;

	MyString fileUsername;
	MyString filePassword;
	unsigned category;

	while (ifs >> fileUsername >> filePassword >> category) {
		if (fileUsername == enteredUsername && filePassword == enteredPassword)
		{
			system("cls");
			if (category == 1)
			{
				std::cout << "Succesfully logged in as a user." << '\n';
				return 1;
			}
			
			if (category == 2)
			{
				std::cout << "Succesfully logged in as an administrator." << '\n';
				return 2;
			}
			
		}
	}
	ifs.close();
	system("cls");
	std::cout << "Account not found" << '\n';
	accountOption();
	return -1;

}

int registerAccount()
{
	std::cout << "Registering a new account." << '\n';
	std::cout << "Enter a username: " << '\n';
	MyString newUsername;
	std::cin >> newUsername;
	std::cout << "Enter a password: " << '\n';
	MyString newPassword;
	std::cin >> newPassword;

	std::ofstream ofs("Accounts.txt", std::ios::app);
	if (!ofs.is_open())
	{
		throw std::runtime_error("Failed to open Accounts.txt");
	}
	ofs << newUsername << " " << newPassword << " 1" << '\n';
	ofs.close();
	system("cls");
	std::cout << "Succesfully created an account." << '\n';
	accountOption();
}