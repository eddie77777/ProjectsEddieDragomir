#pragma once
#include <exception>
#include <string>
#include "OperationStatus.h"

class CodedException : public std::exception
{
public:
	explicit CodedException(const char* code, const char* message);
	explicit CodedException(const OperationStatus::Code code, const std::string& message);

	OperationStatus::Code GetCode() const;
	std::string GetWhat() const;
	std::string GetMessage() const;

	virtual ~CodedException() noexcept;
	virtual const char* what() const noexcept;

protected:
	OperationStatus::Code m_code;
    std::string m_message;
};

