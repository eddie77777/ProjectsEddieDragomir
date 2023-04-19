#include "../include/WatchedMovieDisplayer.h"

WatchedMovieDisplayer::WatchedMovieDisplayer(uint32_t mvId, double r, const std::string& mvTitle)
	: m_movieId(mvId)
	, m_rating(r)
	, m_movieTitle(mvTitle)
{
}

uint32_t WatchedMovieDisplayer::GetMovieId() const
{
	return m_movieId;
}

std::ostream& operator<<(std::ostream& g, const WatchedMovieDisplayer& wmd)
{
	g << wmd.m_movieId << " " << wmd.m_movieTitle << " ";
	return g << std::fixed << std::setprecision(1) << wmd.m_rating << "/5.0";
}