#include <fstream>
#include <iostream>
#include "MyString.h"
#include "Login.h"
#include "Hour.h"


int main()
{
	Hour h1(23, 30);
	h1 = h1 + 91;
	std::cout << h1;
}