#pragma once
#pragma once
#include "MyString.h"
#include <fstream>

void writeStringToFile(std::ofstream& ofs, const MyString& str);
MyString readStringFromFile(std::ifstream& ifs);
int myStringToInt(const MyString& str);

