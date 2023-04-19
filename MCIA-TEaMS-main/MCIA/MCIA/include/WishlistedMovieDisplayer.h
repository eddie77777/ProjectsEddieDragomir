#pragma once
#include <iostream>
#include <iomanip>
#include <cstdint>

class WishlistedMovieDisplayer
{
public:
	WishlistedMovieDisplayer(uint32_t mvId, const std::string& mvTitle);

	uint32_t GetMovieId() const;

	friend std::ostream& operator<<(std::ostream& g, const WishlistedMovieDisplayer& wld);
private:
	uint32_t m_movieId;
	std::string m_movieTitle;
};
