#pragma once
#include "Command.h"
#include "polymorphic_ptr.hpp"
#include "MyString.h"

class CommandFactory
{
public:
	static polymorphic_ptr<Command> createCommand(const MyString& command);
};
