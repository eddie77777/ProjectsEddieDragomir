#pragma once
#include <iostream>
#include <string>
#include <fstream>

#include "ConnectedUser.h"
#include "DatabaseManagement.h"
#include "DBValidation.h"

class AuthService
{
public:
	void RegisterUser(User& user);
	void RegisterUserProcess(User& user);
	void LoginUser(User& user);
	void LogOut();
	bool ExistsUserWithUsername(const std::string& username);
	static uint16_t GetConnectedUserId();
	static std::string GetConnectedUserName();
    static std::vector<uint32_t> GetRecommendedMoviesForCurrentUser();
    static void UpdateRecomMoviesForCurrentUser(uint32_t movieId, float rating);
    void StartAuthProcess();

protected:
	const std::string PATH_QUESTIONS_FILE = "..\\..\\..\\MCIA\\resources\\Questions.txt";
	const std::string PLEASE_ENTER_RATING = "Please enter the rating between 1 and 5: ";
	const std::string OUT_OF_RANGE_RATING = "Out of range rating.\nPlease enter a valid rating value: ";
	const std::string PLEASE_LOGIN = "Please login before entering the application.\n";
	const std::string PLEASE_RETRY = "\n\nPlease retry:\n";

private:
	static std::unique_ptr<ConnectedUser> m_connectedUser;
};

