#define _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS
#pragma warning(disable : 4996)
#include <iostream>
#include <sqlite_orm/sqlite_orm.h>
#include "include/DatabaseManagement.h"
#include "include/AuthService.h"
#include "include/DBPage.h"
#include "include/Movie.h"
#include "include/DBValidation.h"
#include "include/WishlistedMovie.h"
#include "include/OperationStatus.h"
#include "include/MovieService.h"
#include "include/ConsoleInputController.h"
#include "include/RecomSystem.h"
#include <cstdlib>
#include <thread>
#include <future>
#include <cstdlib>
#include <Python.h>

using namespace sqlite_orm;


template<typename T>
void displayTable(T filter, const ConsoleInputController& consoleInputController) 
{
	auto showInstructions = []() {
		std::cout << "Navigate table using [b] (back), [n] (next), [j] (jump to page).\nOther options:\n [r] rate movie\n [w] add to wishlist\n [i] info about movie\n [x] back to menu\n";
		std::cout << "Input character: ";
	};

	char ch;
	int wantedPage = 0;
	auto result = DatabaseManagement::GetInstance().PagedSelect<Movie>(wantedPage, DBPage<Movie>::DEFAULT_ROWS_NUMBER_PER_PAGE, filter);
	uint16_t connectedUserId = AuthService::GetConnectedUserId();
	MovieService ms;
	std::cout << result;
	showInstructions();
	while (std::cin >> ch)
	{
		switch (ch)
		{
		case 'b':
			system("CLS");
			wantedPage = std::max(wantedPage - 1, 0);
			break;
		case 'n':
			system("CLS");
			wantedPage = std::min(wantedPage + 1, result.GetNmbPages() - 1);
			break;
		case 'j':
			std::cout << "Choose page number: ";
			std::cin >> wantedPage;
			system("CLS");
			wantedPage = std::min(wantedPage, result.GetNmbPages() - 1);
			wantedPage = std::max(wantedPage, 0);
			break;
		case 'r':
			{
				std::pair<uint32_t, float> movieIdRating = consoleInputController.gatherMovieRatingInfo(result.GetResults());
				if (movieIdRating.first == UINT32_MAX) {
					system("CLS");
					break;
				}
				try {
					ms.AddMovieToWatchlist(connectedUserId, movieIdRating.first, movieIdRating.second);
					system("CLS");
					std::cout << "Movie rating saved.\n";
				}
				catch (std::exception e) {
					std::cout << e.what();
				}
			}
			break;
		case 'i':
			{
				uint32_t movieId = consoleInputController.gatherMovieIdFromUser(result.GetResults());
				if (movieId == UINT32_MAX) {
					system("CLS");
					break;
				}
				MovieInformationDisplayer movieInfo = ms.GetMovieInformations(movieId);
				std::cout << movieInfo << '\n';
				showInstructions();
				continue;
			}
			break;
		case 'w':
			{
				uint32_t movieId = consoleInputController.gatherMovieIdFromUser(result.GetResults());
				if (movieId == UINT32_MAX) {
					system("CLS");
					break;
				}
				try {
					ms.AddMovieToWishlist(connectedUserId, movieId);
					system("CLS");
					std::cout << "Movie added to wishlist.\n";
				}
				catch (std::exception e) {
					std::cout << e.what();
				}
			}
			break;
		case 'x':
			system("CLS");
			return;
		default:
			std::cout << "Input character: ";
			continue;
		}
		result = DatabaseManagement::GetInstance().PagedSelect<Movie>(wantedPage, DBPage<Movie>::DEFAULT_ROWS_NUMBER_PER_PAGE, filter);
		std::cout << result;
		showInstructions();
	}
}

void displayWatchedList(const ConsoleInputController& consoleInputController)
{
	auto showInstructions = [](){
		std::cout << "Navigate table using [b] (back), [n] (next), [j] (jump to page).\nOther options:\n [i] info about movie\n [x] back to menu\n";
		std::cout << "Input character: ";
	};
	MovieService ms;
	char ch;
	uint16_t connectedUserId = AuthService::GetConnectedUserId();
	int wantedPage = 0;
	auto result = ms.GetWatchedMoviesOfUser(connectedUserId, wantedPage, DBPage<WatchedMovieDisplayer>::DEFAULT_ROWS_NUMBER_PER_PAGE);
	std::cout << result;
	showInstructions();
	while (std::cin >> ch)
	{
		switch (ch)
		{
		case 'b':
			system("CLS");
			wantedPage = std::max(wantedPage - 1, 0);
			break;
		case 'n':
			system("CLS");
			wantedPage = std::min(wantedPage + 1, result.GetNmbPages() - 1);
			break;
		case 'j':
			std::cout << "Choose page number: ";
			std::cin >> wantedPage;
			system("CLS");
			wantedPage = std::min(wantedPage, result.GetNmbPages() - 1);
			wantedPage = std::max(wantedPage, 0);
			break;
		case 'i':
			{
				uint32_t movieId = consoleInputController.gatherMovieIdFromUser(result.GetResults(), false);
				if (movieId == UINT32_MAX) {
					system("CLS");
					break;
				}
				MovieInformationDisplayer movieInfo = ms.GetMovieInformations(movieId);
				std::cout << movieInfo << '\n';
				showInstructions();
				continue;
			}
			break;
		case 'x':
			system("CLS");
			return;
		default:
			std::cout << "Input character: ";
			continue;
		}
		result = ms.GetWatchedMoviesOfUser(connectedUserId, wantedPage, DBPage<WatchedMovieDisplayer>::DEFAULT_ROWS_NUMBER_PER_PAGE);
		std::cout << result;
		showInstructions();
	}
}

void displayWishList(const ConsoleInputController& consoleInputController)
{
	auto showInstructions = []() {
		std::cout << "Navigate table using [b] (back), [n] (next), [j] (jump to page).\nOther options:\n [d] remove movie from wishlist\n [i] info about movie\n [r] rate movie\n [x] back to menu\n";
		std::cout << "Input character: ";
	};
	MovieService ms;
	char ch;
	uint16_t connectedUserId = AuthService::GetConnectedUserId();
	int wantedPage = 0;
	auto result = ms.GetWishListOfUser(connectedUserId, wantedPage, DBPage<WishlistedMovieDisplayer>::DEFAULT_ROWS_NUMBER_PER_PAGE);
	std::cout << result;
	showInstructions();
	while (std::cin >> ch)
	{
		switch (ch)
		{
		case 'b':
			system("CLS");
			wantedPage = std::max(wantedPage - 1, 0);
			break;
		case 'n':
			system("CLS");
			wantedPage = std::min(wantedPage + 1, result.GetNmbPages() - 1);
			break;
		case 'j':
			std::cout << "Choose page number: ";
			std::cin >> wantedPage;
			system("CLS");
			wantedPage = std::min(wantedPage, result.GetNmbPages() - 1);
			wantedPage = std::max(wantedPage, 0);
			break;
		case 'd':
			{
				if (result.IsPageEmpty()) {
					system("CLS");
					std::cout << "You cannot delete from an empty list.\n";
					break;
				}
				uint32_t movieId = consoleInputController.gatherMovieIdFromUser(result.GetResults(), false);
				if (movieId == UINT32_MAX) {
					system("CLS");
					break;
				}
				try {
					ms.RemoveMovieFromWishlist(connectedUserId, movieId);
				}
				catch (std::exception e) {
					std::cout << e.what();
				}
				system("CLS");
			}
			break;
		case 'i':
			{
				uint32_t movieId = consoleInputController.gatherMovieIdFromUser(result.GetResults(), false);
				if (movieId == UINT32_MAX) {
					system("CLS");
					break;
				}
				MovieInformationDisplayer movieInfo = ms.GetMovieInformations(movieId);
				std::cout << movieInfo << '\n';
				showInstructions();
				continue;
			}
			break;
		case 'r':
		{
			std::pair<uint32_t, float> movieIdRating = consoleInputController.gatherMovieRatingInfo(result.GetResults(), false);
			if (movieIdRating.first == UINT32_MAX) {
				system("CLS");
				break;
			}
			try {
				ms.MoveMovieFromWishlistToWatched(connectedUserId, movieIdRating.first, movieIdRating.second);
				system("CLS");
				std::cout << "Movie rating saved.\n";
			}
			catch (std::exception e) {
				std::cout << e.what();
			}
		}
		break;
		case 'x':
			system("CLS");
			return;
		default:
			std::cout << "Input character: ";
			continue;
		}
		result = ms.GetWishListOfUser(connectedUserId, wantedPage, DBPage<WishlistedMovieDisplayer>::DEFAULT_ROWS_NUMBER_PER_PAGE);
		std::cout << result;
		showInstructions();
	}
}

void displayRecommendedMovies(const ConsoleInputController& consoleInputController)
{
	char ch;
	MovieService ms;
	std::vector<uint32_t> moviesId = AuthService::GetRecommendedMoviesForCurrentUser();
	uint16_t connectedUserId = AuthService::GetConnectedUserId();
	auto moviesPage = ms.ParseRecommendedMovies(connectedUserId, moviesId, 0);
	std::cout << moviesPage;
	auto showInstructions = []() {
		std::cout << "Pick an option:\n [i] info about movie\n [r] rate movie\n [w] add to wishlist\n [x] back to menu\n";
		std::cout << "Input character: ";
	};
	showInstructions();
	while (std::cin >> ch)
	{
		switch (ch)
		{
		case 'r':
		{
			std::pair<uint32_t, float> movieIdRating = consoleInputController.gatherMovieRatingInfo(moviesPage.GetResults(), false);
			if (movieIdRating.first == UINT32_MAX) {
				system("CLS");
				break;
			}
			try {
				ms.AddMovieToWatchlist(connectedUserId, movieIdRating.first, movieIdRating.second);
				system("CLS");
				std::cout << "Movie rating saved.\n";
			}
			catch (std::exception e) {
				std::cout << e.what();
			}
		}
		break;
		case 'i':
		{
			uint32_t movieId = consoleInputController.gatherMovieIdFromUser(moviesPage.GetResults(), false);
			if (movieId == UINT32_MAX) {
				system("CLS");
				break;
			}
			MovieInformationDisplayer movieInfo = ms.GetMovieInformations(movieId);
			std::cout << movieInfo << '\n';
			showInstructions();
			continue;
		}
		break;
		case 'w':
		{
			uint32_t movieId = consoleInputController.gatherMovieIdFromUser(moviesPage.GetResults(), false);
			if (movieId == UINT32_MAX) {
				system("CLS");
				break;
			}
			try {
				ms.AddMovieToWishlist(connectedUserId, movieId);
				system("CLS");
				std::cout << "Movie added to wishlist.\n";
			}
			catch (std::exception e) {
				std::cout << e.what();
			}
		}
		break;
		case 'x':
			system("CLS");
			return;
		default:
			std::cout << "Input character: ";
			continue;
		}
		std::cout << moviesPage;
		showInstructions();
	}
}

int main()
{
	char ch;
	bool isSearching = false;
	std::string movieName;
	DBValidation validate;
	ConsoleInputController consoleInputController;
	AuthService authService;
	authService.StartAuthProcess();
	system("CLS");
	std::cout << "Welcome, " << AuthService::GetConnectedUserName() << "!\n\n";

	uint16_t connectedUserId = AuthService::GetConnectedUserId();
	while (true)
	{
		std::cout << "Please choose what to do : \n \
[a] all movies browsing\n \
[s] search movie by name\n \
[v] my watched list\n \
[w] my wishlist\n \
[r] recommend me something\n \
[q] quit\n \
[x] log out.\n\
Enter an option: ";
		std::cin >> ch;
		system("CLS");
		switch (ch) {
		case 'a':
		case 's':
			{ //<-- temporary solution, this scope should be removed
				if (ch == 'a') {
					isSearching = false;
				}
				else {
					isSearching = true;
					std::cout << "Please enter a movie name: ";
					std::cin >> movieName;
					system("CLS");
				}
				std::string query = "%" + movieName + "%";
				auto allFilter = c(&Movie::GetId) >= 0;
				auto movieNameFilter = like(&Movie::GetTitle, query);

				if (isSearching)
					displayTable(movieNameFilter, consoleInputController);
				else displayTable(allFilter, consoleInputController);
			}
			break;
		case 'v':
			displayWatchedList(consoleInputController);
			break;
		case 'w':
			displayWishList(consoleInputController);
			break;
		case 'x':
			authService.LogOut();
			break;
        case 'r': {
			displayRecommendedMovies(consoleInputController);
            break;
        }
		case 'q':
			return 0;
		default:
			std::cout << "Invalid option.\n";
			break;
		}
	}
	
	return 0;
}