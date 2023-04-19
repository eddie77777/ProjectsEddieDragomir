#pragma once
#include <string>
#include <map>
#include "OperationStatus.h"

class OperationStatusToMessage {
public:
	OperationStatusToMessage();
	
	template<typename... Args>
	std::string GetMessage(OperationStatus::Code code, Args... args);
private:
	template<typename T, typename... Args>
	std::string GetMessageFromBase(std::string& base, T value, Args... args);

	template<typename T, typename... Args>
	std::string GetMessageFromBase(std::string& base, T last);

private:
	static const std::unordered_map<OperationStatus::Code, std::string> m_codeToMessage;
};

template<typename ...Args>
inline std::string OperationStatusToMessage::GetMessage(OperationStatus::Code code, Args ...args)
{
	std::string baseString = m_codeToMessage.at(code);
	return GetMessageFromBase(baseString, args...);
}

template<typename T, typename ...Args>
std::string OperationStatusToMessage::GetMessageFromBase(std::string& base, T value, Args ...args)
{
	size_t posOfMod = base.find_first_of("%");
	if (posOfMod == -1)
		return base;
	base.erase(posOfMod, 1);
	if constexpr(std::is_convertible<T, std::string>::value)
		base.insert(posOfMod, std::string(value));
	else
		base.insert(posOfMod, std::to_string(value));
	return GetMessageFromBase(base, args...);
}

template<typename T, typename ...Args>
std::string OperationStatusToMessage::GetMessageFromBase(std::string& base, T last) {
	size_t posOfMod = base.find_first_of("%");
	if (posOfMod == -1)
		return base;
	base.erase(posOfMod, 1);
	if constexpr(std::is_convertible<T, std::string>::value)
		base.insert(posOfMod, std::string(last));
	else
		base.insert(posOfMod, std::to_string(last));
	return base;
}