#pragma once
#include "DBPage.h"
#include "DatabaseManagement.h"
#include "WatchedMovieDisplayer.h"
#include "WishlistedMovieDisplayer.h"
#include "MovieInformationDisplayer.h"

class MovieService {
public:	
	DBPage<WatchedMovieDisplayer> GetWatchedMoviesOfUser(const uint16_t userId, const int page, const int nmbRowsPerPage);
	DBPage<WishlistedMovieDisplayer> GetWishListOfUser(const uint16_t userId, const int page, const int nmbRowsPerPage);
	DBPage<Movie> ParseRecommendedMovies(const uint16_t userId, const std::vector<uint32_t>& movieIds, const int page);
	MovieInformationDisplayer GetMovieInformations(const uint32_t id);
	void AddMovieToWatchlist(const uint16_t userId, const uint32_t movieId, const float rating);
	void RemoveMovieFromWatchlist(const uint16_t userId, const uint32_t movieId);
	void AddMovieToWishlist(const uint16_t userId, const uint32_t movieId);
	void RemoveMovieFromWishlist(const uint16_t userId, const uint32_t movieId);
	void MoveMovieFromWishlistToWatched(const uint16_t userId, const uint32_t movieId, const float rating);

private:
	std::vector<uint32_t> GetAllWatchedMoviesIdsOfUser(const uint16_t userId);
};