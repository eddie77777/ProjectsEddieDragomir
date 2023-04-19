#include "../include/WishlistedMovieDisplayer.h"

WishlistedMovieDisplayer::WishlistedMovieDisplayer(uint32_t mvId, const std::string& mvTitle)
	: m_movieId(mvId)
	, m_movieTitle(mvTitle)
{
}

uint32_t WishlistedMovieDisplayer::GetMovieId() const
{
	return m_movieId;
}

std::ostream& operator<<(std::ostream& g, const WishlistedMovieDisplayer& wld)
{
	return g << wld.m_movieId << " " << wld.m_movieTitle;
}