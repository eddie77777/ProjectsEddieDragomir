#pragma once

#include <vector>
#include <stdlib.h>
#include "Movie.h"
#include "DBValidation.h"
#include <cstdint>

class ConsoleInputController {
public:

	template<class T>
	uint32_t gatherMovieIdFromUser(const std::vector<T>& displayedPage, const bool& allowMovieNotInPage = true, std::ostream& out = std::cout, std::istream& in = std::cin) const;
  
	template <class T>
	std::pair<uint32_t, float> gatherMovieRatingInfo(const std::vector<T>& displayedPage, const bool& allowMovieNotInPage = true, std::ostream& out = std::cout, std::istream& in = std::cin) const;

public:
	const std::string OUT_PICK_ID = "Please enter the id of the movie you want to pick or [q] to quit: ";
	const std::string OUT_ASK_VALID_ID = "Please enter a valid id, or press [q] to quit: ";
	const std::string OUT_ID_NOT_IN_PAGE_CONFIRM = "This id doesn't appear to be on this page. Are you sure you want to proceed?\n [y]/[n]: ";
	const std::string OUT_ID_NOT_IN_PAGE_NOT_ALLOWED = "This id doesn't appear to be on this page.\nPlease choose one that is displayed above, or press [q] to quit: ";
	const std::string OUT_PICK_RATING = "Please enter the rating between 1 and 5: ";
	const std::string OUT_RATING_OUT_OF_RANGE = "Out of range rating.\nPlease enter a valid rating value: ";
};

template<class T>
std::pair<uint32_t, float> ConsoleInputController::gatherMovieRatingInfo(const std::vector<T>& displayedPage, const bool& allowMovieNotInPage, std::ostream& out, std::istream& in) const
{
	char ch = 0;
	std::pair<uint32_t, float> movieRatingPair;
	std::string inputString;
	movieRatingPair.first = gatherMovieIdFromUser(displayedPage, allowMovieNotInPage, out, in);
	if (movieRatingPair.first == UINT32_MAX)
		return { UINT32_MAX, UINT32_MAX };
	out << OUT_PICK_RATING;
	//This checks if the rating for the movie to add in watched list table is valid or out of range.
	while (true)
	{
		in >> inputString;
		if (inputString.size() == 1 && inputString[0] == 'q')
			return { UINT32_MAX, UINT32_MAX };
		try
		{
			size_t maximumRatingValueLength = 3;
			if (inputString.size() <= maximumRatingValueLength)
			{
				movieRatingPair.second = std::stof(inputString);
				if (movieRatingPair.second < 1.0f || movieRatingPair.second > 5.0f)
					out << OUT_RATING_OUT_OF_RANGE;
				else
					break;
			}
			else
				out << OUT_RATING_OUT_OF_RANGE;
		}
		catch (std::invalid_argument e)
		{
			out << OUT_RATING_OUT_OF_RANGE;
		}
	}
	return movieRatingPair;
}

template<>
inline uint32_t ConsoleInputController::gatherMovieIdFromUser(const std::vector<Movie>& displayedPage, const bool& allowMovieNotInPage, std::ostream& out, std::istream& in) const
{
	char ch;
	uint32_t movieId;
	DBValidation validate;
	std::string inputString;

	out << OUT_PICK_ID;
	//This checks if the id of the movie to pick exists or not)
	while (true)
	{
		in >> inputString;
		if (inputString.size() == 1 && inputString[0] == 'q')
			return UINT32_MAX;
		if (inputString.size() > 9) {
			out << OUT_ASK_VALID_ID;
			continue;
		}
		try {
			movieId = std::stoi(inputString);
		}
		catch (std::invalid_argument e) {
			out << OUT_ASK_VALID_ID;
			continue;
		}
		if (!std::any_of(displayedPage.begin(), displayedPage.end(),
			[&](const Movie& movie) { return movie.GetId() == movieId; }))
		{
			if (!allowMovieNotInPage) {
				out << OUT_ID_NOT_IN_PAGE_NOT_ALLOWED;
				continue;
			}
			out << OUT_ID_NOT_IN_PAGE_CONFIRM;
			in >> ch;
			if (ch == 'y' && !DatabaseManagement::GetInstance().IdExists<Movie>(movieId) || ch != 'y') {
				out << OUT_ASK_VALID_ID;
			}
			else break;
			continue;
		}
		break;
	}
	return movieId;
}

template<class T>
uint32_t ConsoleInputController::gatherMovieIdFromUser(const std::vector<T>& displayedPage, const bool& allowMovieNotInPage, std::ostream& out, std::istream& in) const
{
	char ch;
	uint32_t movieId;
	DBValidation validate;
	std::string inputString;

	out << OUT_PICK_ID;
	//This checks if the id of the movie to pick exists or not)
	while (true)
	{
		in >> inputString;
		if (inputString.size() == 1 && inputString[0] == 'q')
			return UINT32_MAX;
		if (inputString.size() > 9) {
			out << OUT_ASK_VALID_ID;
			continue;
		}
		try {
			movieId = std::stoi(inputString);
		}
		catch (std::invalid_argument e) {
			out << OUT_ASK_VALID_ID;
			continue;
		}
		if (!std::any_of(displayedPage.begin(), displayedPage.end(),
			[&movieId](const T& movie) { return movie.GetMovieId() == movieId; }))
		{
			if (!allowMovieNotInPage) {
				out << OUT_ID_NOT_IN_PAGE_NOT_ALLOWED;
				continue;
			}	
			out << OUT_ID_NOT_IN_PAGE_CONFIRM;
			in >> ch;
			if (ch == 'y' && !DatabaseManagement::GetInstance().IdExists<Movie>(movieId) || ch != 'y') {
				out << OUT_ASK_VALID_ID;
			}
			else break;
			continue;
		}
		break;
	}
	return movieId;
}
