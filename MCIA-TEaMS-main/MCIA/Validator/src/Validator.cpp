#include "../include/Validator.h"
#include <algorithm>
using namespace std;

bool Validator::IsAlphaNumericOrSpecial(const std::string& string)
{
    auto isNotAlphaNumericCaller = [&](char c) { return this->IsNotAlphaNumericOrSpecial(c); };
    return find_if(string.begin(), string.end(), isNotAlphaNumericCaller) == string.end();
}

bool Validator::IsBlank(const std::string& string)
{
    auto isNotBlankCaller = [&](char c) { return this->IsNotBlank(c); };
    return string.size() == 0 || find_if(string.begin(), string.end(), isNotBlankCaller) == string.end();
}

bool Validator::IsNotBlank(const char c)
{
    return !isblank(c);
}

bool Validator::IsNotAlphaNumericOrSpecial(const char c)
{
    return !(isalnum(c) || c == '_' || c == '.');
}
