#pragma once
#include "CinemaSystem.h"
class Program
{
	
public:
	CinemaSystem& system = CinemaSystem::getInstance();
	Program();

	void run();

	~Program();

private:
	void loop();
	void save();

};

