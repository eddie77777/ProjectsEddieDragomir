#pragma once
#include <string>

class Validator
{
public:
	bool IsAlphaNumericOrSpecial(const std::string& string);
	bool IsBlank(const std::string& string);
	bool IsNotBlank(const char c);
	bool IsNotAlphaNumericOrSpecial(const char c);
};

