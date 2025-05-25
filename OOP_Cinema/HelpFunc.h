#pragma once
#pragma once
#include "MyString.h"
#include <fstream>

void writeStringToTextFile(std::ofstream& ofs, const MyString& str);
MyString readStringFromTextFile(std::ifstream& ifs);
int myStringToInt(const MyString& str);

