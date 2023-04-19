#pragma once
#include <iostream>
#include <cstdint>
#include <string>
#include "NamedAsciiChars.h"

class MovieInformationDisplayer
{
public:
	MovieInformationDisplayer(uint32_t id, const std::string& title, const uint16_t releaseYear, const std::string genres = "");
	
	void AddGenre(const std::string& genre);

	uint32_t GetMovieId() const;
	std::string GetTitle() const;
	uint16_t GetReleaseYear() const;
	std::string GetGenres() const;

	friend std::ostream& operator<<(std::ostream& g, const MovieInformationDisplayer& mid);
private:
	uint32_t m_movieId;
	std::string m_title;
	uint16_t m_releaseYear;
	std::string m_genres;
};
