#include "../include/WishlistedMovie.h"

WishlistedMovie::WishlistedMovie(const uint16_t user_id, const uint32_t movie_id)
	:m_user_id(user_id)
	,m_movie_id(movie_id)
{
}

uint16_t WishlistedMovie::GetUserId() const
{
	return m_user_id;
}

uint32_t WishlistedMovie::GetMovieId() const
{
	return m_movie_id;
}

void WishlistedMovie::SetUserId(const uint16_t user_id)
{
	m_user_id = user_id;
}

void WishlistedMovie::SetMovieId(const uint32_t movie_id)
{
	m_movie_id = movie_id;
}
