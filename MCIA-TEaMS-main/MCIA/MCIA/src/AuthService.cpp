#include "../include/AuthService.h"
#include <sstream>
#include <exception>
#include "../include/MovieService.h"
#include "../include/RecomSystem.h"

std::unique_ptr<ConnectedUser> AuthService::m_connectedUser = nullptr;


void AuthService::RegisterUser(User& user)
{
	DBValidation validate;
	OperationStatus username_valid = validate.IsUsernameValid(user.GetName());
	OperationStatus pw_valid = validate.IsPasswordValid(user.GetPassword());
	if (!username_valid)
		throw CodedException(username_valid.GetCode(), "username");
	if (!pw_valid)
		throw CodedException(pw_valid.GetCode(), "password");
	if (ExistsUserWithUsername(user.GetName()))
		throw CodedException("username", "A user with this username already exists.");
	uint16_t insertedUserId = DatabaseManagement::GetInstance().InsertElement(user);
	user.SetId(insertedUserId);
	m_connectedUser = std::make_unique<ConnectedUser>(user);
	
	//m_connectedUser->GetRecomService().SetCurrentUserId(insertedUserId);
}

void AuthService::RegisterUserProcess(User& user)
{
	DatabaseManagement::GetInstance().GetStorage().begin_transaction();
	try {
		RegisterUser(user);
	}
	catch (CodedException e) {
		DatabaseManagement::GetInstance().GetStorage().rollback();
		throw e;
	}

	std::ifstream f;
	f.open(PATH_QUESTIONS_FILE.c_str());
	if (f.fail() || f.bad()) {
		DatabaseManagement::GetInstance().GetStorage().rollback();
		throw CodedException(OperationStatus::Code::RES_NOT_FOUND, "An error occured. Please try again later.");
	}

	std::cout << "Welcome, " << user.GetName() << "! Please rate some movies first: \n\n";
	uint32_t id_movie;
	std::string srating;
	float rating;

	while (f >> id_movie)
	{
		std::cout << "For the movie\n";
		MovieService ms;
		MovieInformationDisplayer movieInfo = ms.GetMovieInformations(id_movie);
		std::cout << movieInfo << '\n';

		std::cout << PLEASE_ENTER_RATING;
		//This checks if the rating for the movie to add in watched list table is valid or out of range.
		while (true)
		{
			std::cin >> srating;
			try {
				size_t maximumRatingValueLenght = 3;
				if (srating.size() <= maximumRatingValueLenght)
				{
					rating = std::stof(srating);
					if (rating < 1.0f || rating > 5.0f)
						std::cout << OUT_OF_RANGE_RATING;
					else
						break;
				}
				else
					std::cout << OUT_OF_RANGE_RATING;
			}
			catch (std::invalid_argument e)
			{
				std::cout << OUT_OF_RANGE_RATING;
			}
		}

		//WatchedMovie watchedMovie(m_connectedUser->GetUser().GetId(), id_movie, rating);// (static_cast<uint16_t>(user_id), static_cast<uint16_t>(movie_id), static_cast<uint8_t>(rating));
		try {
			ms.AddMovieToWatchlist(m_connectedUser->GetUser().GetId(), id_movie, rating);
			//DatabaseManagement::GetInstance().GetStorage().replace(watchedMovie);
		}
		catch (std::exception e) {
			std::cout << e.what();
			DatabaseManagement::GetInstance().GetStorage().rollback();
		}
		system("CLS");
	}
	DatabaseManagement::GetInstance().GetStorage().commit();
	f.close();
	LogOut();
}


void AuthService::LoginUser(User& user)
{
	if (user.GetPassword() != DatabaseManagement::GetInstance().GetElementByColumnValue(&User::GetName, user.GetName()).GetPassword())
		throw CodedException(OperationStatus::Code::DB_USER_INVALID_PASSWORD, "Incorrect password.");
	m_connectedUser = std::make_unique<ConnectedUser>(DatabaseManagement::GetInstance().GetElementByColumnValue(&User::GetName, user.GetName()));
    m_connectedUser->GetRecomService().StartPopulatingRecommendedMovies();
}

void AuthService::StartAuthProcess()
{
	char c;
	bool isRegistering = false;
	std::string name, pw;
	auto& dbm = DatabaseManagement::GetInstance();

	std::cout << PLEASE_LOGIN;

	while (true)
	{
		std::cout << "Username: ";
		std::cin >> name;
		std::cout << "Password: ";
		std::cin >> pw;

		if (name == "x") {
			exit(0);
		}
			
		User user(name, pw);
		isRegistering = false;

		if (!ExistsUserWithUsername(name))
		{
			std::cout << "There is no account with username " + name + ":\n [r] register\t[x] back to login\nPlease choose: ";
			std::cin >> c;
			if (c == 'x')
				continue;
			isRegistering = true;
		}
		try {
			if (isRegistering)
				AuthService::RegisterUserProcess(user);
			else
				AuthService::LoginUser(user);
			break;
		}
		catch (CodedException e) {
			DBValidation validate;
			if (isRegistering) {
				if (e.GetMessage() == "username")
					std::cout << validate.UsernameErrorMessage(e.GetCode());
				else if (e.GetMessage() == "password")
					std::cout << validate.PasswordErrorMessage(e.GetCode());
				else std::cout << e.what();
				std::cout << PLEASE_RETRY;
			}
			else std::cout << e.what() << "\n\n";
		}
		catch (std::exception e) {
			std::cout << e.what() << "\n\n";
		}
	}
}

bool AuthService::ExistsUserWithUsername(const std::string& username)
{
	auto result = DatabaseManagement::GetInstance().GetStorage().get_all<User>(where(c(&User::GetName) == username));
	return !(result.empty());
}

void AuthService::LogOut()
{
	m_connectedUser.release();
	StartAuthProcess();
}	

uint16_t AuthService::GetConnectedUserId() // TODO: throw exception if user isnt connected
{
	return m_connectedUser->GetUser().GetId();
}

std::string AuthService::GetConnectedUserName()
{
	return m_connectedUser->GetUser().GetName();
}

std::vector<uint32_t> AuthService::GetRecommendedMoviesForCurrentUser() {
    return m_connectedUser->GetRecomService().GetRecommendedMovies();
}

void AuthService::UpdateRecomMoviesForCurrentUser(uint32_t movieId, float rating) {
    m_connectedUser->GetRecomService().StartUpdatingMovie(movieId, rating);
}
