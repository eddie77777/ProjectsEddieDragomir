#include "../include/OperationStatus.h"


const std::unordered_map<std::string, OperationStatus::Code> OperationStatus::m_conversionMap{
	  { "Valid", Code::SUCCESS}
	, { "Blank", Code::F_BLANK }
	, { "Size", Code::F_SIZE }
	, { "AlphaNumeric", Code::F_ALPHA_NUMERIC }
	, { "Trim", Code::F_TRIM }
	, { "InvalidPattern", Code::F_INVALID_PATTERN }
	, { "InvalidEntity", Code::DB_INVALID_ENTITY }
	, { "EntityNotFound", Code::DB_ENTITY_NOT_FOUND }
	, { "InvalidUser", Code::DB_USER_INVALID_PASSWORD }
	, { "InvalidId", Code::DB_INVALID_ID }
	, { "ResNotFound", Code::RES_NOT_FOUND }
	, { "PyModuleNotFound", Code::PY_MODULE_NOT_FOUND }
	, { "PyFunctionNotFound", Code::PY_FUNCTION_NOT_FOUND }
};


OperationStatus::OperationStatus(const Code& c)
	: m_code(c)
{
}

std::string OperationStatus::CodeToString(const OperationStatus::Code& code)
{
	switch (code) {
	case Code::SUCCESS:
		return "Valid";
	case Code::F_BLANK:
		return "Blank";
	case Code::F_SIZE:
		return "Size";
	case Code::F_ALPHA_NUMERIC:
		return "AlphaNumeric";
	case Code::F_TRIM:
		return "Trim";
	case Code::F_INVALID_PATTERN:
		return "InvalidPattern";
	case Code::DB_INVALID_ENTITY:
		return "InvalidEntity";
	case Code::DB_ENTITY_NOT_FOUND:
		return "EntityNotFound";
	case Code::DB_USER_INVALID_PASSWORD:
		return "InvalidUser";
	case Code::DB_INVALID_ID:
		return "InvalidId";
	case Code::RES_NOT_FOUND:
		return "ResNotFound";
	case Code::PY_MODULE_NOT_FOUND:
		return "PyModuleNotFound";
	case Code::PY_FUNCTION_NOT_FOUND:
		return "PyFunctionNotFound";
	default:
		return "Err";
	}
}
OperationStatus::Code OperationStatus::StringToCode(const std::string& str)
{
	return OperationStatus::m_conversionMap.at(str);
}

OperationStatus::Code OperationStatus::GetCode() const
{
	return m_code;
}

bool OperationStatus::operator!=(const OperationStatus& cmp)
{
    return m_code != cmp.m_code;
}

bool OperationStatus::operator==(const OperationStatus& cmp)
{
    return m_code == cmp.m_code;
}

bool OperationStatus::operator!=(const bool cmp)
{
    if (cmp)
        return m_code != Code::SUCCESS;
    return m_code == Code::SUCCESS;
}

OperationStatus& OperationStatus::operator=(const OperationStatus& opStatus)
{
	m_code = opStatus.m_code;
	return *this;
}

bool OperationStatus::operator==(const bool cmp)
{
    return !(*this != cmp);
}

OperationStatus::operator bool()
{
    return m_code == Code::SUCCESS;
}

OperationStatus::operator std::string()
{
	return OperationStatus::CodeToString(m_code);
}