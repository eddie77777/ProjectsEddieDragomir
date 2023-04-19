#pragma once
#include <string>	
#include <iostream>
#include "OperationStatus.h"
#include "DatabaseManagement.h"
#include "OperationStatusToMessage.h"
#include <Validator.h>
#include <regex>

class DBValidation
{
public:
	OperationStatus IsUsernameValid(const std::string& username);
	std::string UsernameErrorMessage(const OperationStatus& status);
	OperationStatus IsPasswordValid(const std::string& password);
	std::string PasswordErrorMessage(const OperationStatus& status);

private:
	static const int kMinUsernameLength = 3;
	static const int kMinPasswordLength = 3;
	static const std::regex kPasswordRegex;
	static const std::string kPasswordRegexMessage;
private:
	Validator m_validator;
	OperationStatusToMessage m_statusToMessage;
};