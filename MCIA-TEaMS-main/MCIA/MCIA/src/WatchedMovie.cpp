#include "../include/WatchedMovie.h"

WatchedMovie::WatchedMovie(const uint16_t user_id, const uint32_t movie_id, const float rating)
	: m_user_id(user_id)
	, m_movie_id(movie_id)
	, m_rating(rating)
{
}

uint16_t WatchedMovie::GetUserId() const
{
	return m_user_id;
}

uint32_t WatchedMovie::GetMovieId() const
{
	return m_movie_id;
}

float WatchedMovie::GetRating() const
{
	return m_rating;
}

void WatchedMovie::SetUserId(const uint16_t user_id)
{
	m_user_id = user_id;
}

void WatchedMovie::SetMovieId(const uint32_t movie_id)
{
	m_movie_id = movie_id;
}

void WatchedMovie::SetRating(const float rating)
{
	m_rating = rating;
}
