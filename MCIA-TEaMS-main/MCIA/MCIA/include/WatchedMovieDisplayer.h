#pragma once
#include <iostream>
#include <iomanip>
#include <cstdint>

class WatchedMovieDisplayer 
{
public:
	WatchedMovieDisplayer(uint32_t mvId, double r, const std::string& mvTitle);

	uint32_t GetMovieId() const;

	friend std::ostream& operator<<(std::ostream& g, const WatchedMovieDisplayer& wmd);
private:
	uint32_t m_movieId;
	std::string m_movieTitle;
	double m_rating;
};