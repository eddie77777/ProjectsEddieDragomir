#pragma once
#include <cstdint>
class WishlistedMovie
{
public:
	WishlistedMovie() = default;
	WishlistedMovie(const uint16_t user_id, const uint32_t movie_id);

	uint16_t GetUserId() const;
	uint32_t GetMovieId() const;

	void SetUserId(const uint16_t user_id);
	void SetMovieId(const uint32_t movie_id);

private:
	uint16_t m_user_id;
	uint32_t m_movie_id;
};

