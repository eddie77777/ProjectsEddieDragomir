#pragma once
#include <cstdint>

class MovieGenre
{
public:
	MovieGenre() = default;
	MovieGenre(const uint32_t movieId, const uint16_t genreId);

	uint32_t GetMovieId() const;
	uint16_t GetGenreId() const;

	void SetMovieId(const uint32_t movieId);
	void SetGenreId(const uint16_t genreId);

	void LinkGenreMovie();
private:
	uint32_t m_movieId;
	uint16_t m_genreId;
};

