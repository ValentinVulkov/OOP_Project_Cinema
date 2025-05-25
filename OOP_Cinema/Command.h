#pragma once
#include "CinemaSystem.h"
#include "User.h"
#include "MyVector.hpp"
#include "MyString.h"

#pragma once
#include "CinemaSystem.h"
#include <iostream>
#include <stdexcept>

class Command
{
public:
	virtual void execute(CinemaSystem* system) const = 0;
	virtual Command* clone() const = 0;
	virtual ~Command() = default;


	
};




