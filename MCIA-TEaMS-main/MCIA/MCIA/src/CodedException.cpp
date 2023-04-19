#include "../include/CodedException.h"
#include <cstring>

CodedException::CodedException(const char* code, const char* message)
	:exception(std::string("[" + std::string(code) + "]" + message).c_str())
{
	m_code = OperationStatus::StringToCode(code);
}

CodedException::CodedException(const OperationStatus::Code code, const std::string& message)
	:exception(std::string("[" + OperationStatus::CodeToString(code) + "]" + message).c_str())
{
	m_code = code;
}

OperationStatus::Code CodedException::GetCode() const
{
	return m_code;
}

std::string CodedException::GetWhat() const
{
	return std::string(what());
}

std::string CodedException::GetMessage() const
{
	std::string fullMessage = GetWhat();
	int lastParanthesesPos = fullMessage.find_last_of("]") + 1;
	return fullMessage.substr(lastParanthesesPos, fullMessage.size() - lastParanthesesPos);
}

CodedException::~CodedException() noexcept
{

}

const char* CodedException::what() const noexcept
{
	return exception::what();
}
