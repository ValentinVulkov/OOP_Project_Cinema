#include "HelpFunc.h"

void writeStringToFile(std::ofstream& ofs, const MyString& str)
{
	int len = str.getSize();
	ofs.write((const char*)&len, sizeof(len));
	ofs.write((const char*)str.c_str(), str.getSize() * sizeof(char));
}

MyString readStringFromFile(std::ifstream& ifs)
{
	int len = 0;

	ifs.read((char*)&len, sizeof(len));

	char* buff = new char[len + 1] {};

	ifs.read((char*)buff, sizeof(char) * len);

	buff[len] = '\0';

	MyString toReturn = buff;

	delete[] buff;

	return toReturn;
}

int myStringToInt(const MyString& str) {
	int result = 0;
	for (unsigned i = 0; i < str.getSize(); i++) {
		if (str[i] < '0' || str[i] > '9') {
			throw std::invalid_argument("Invalid number format");
		}
		result = result * 10 + (str[i] - '0');
	}
	return result;
}