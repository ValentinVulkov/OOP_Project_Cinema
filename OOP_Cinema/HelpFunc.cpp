#include "HelpFunc.h"

void writeStringToTextFile(std::ofstream& ofs, const MyString& str) {
	ofs << str.c_str() << "\n"; // Write string followed by newline
}

MyString readStringFromTextFile(std::ifstream& ifs) {
	char buffer[256];
	ifs.getline(buffer, 256);
	return MyString(buffer);
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