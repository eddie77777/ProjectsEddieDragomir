#pragma once
#include <cstdint>

class WatchedMovie {
public:
	WatchedMovie() = default;
	WatchedMovie(const uint16_t user_id, const uint32_t movie_id, const float rating);

	uint16_t GetUserId() const;
	uint32_t GetMovieId() const;
	float GetRating() const;

	void SetUserId(const uint16_t user_id);
	void SetMovieId(const uint32_t movie_id);
	void SetRating(const float rating);

private:
	uint16_t m_user_id;
	uint32_t m_movie_id;
	float m_rating; 
};