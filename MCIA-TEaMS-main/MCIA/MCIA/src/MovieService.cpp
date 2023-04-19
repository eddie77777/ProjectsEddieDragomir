#include "../include/MovieService.h"
#include "../include/AuthService.h"

DBPage<WatchedMovieDisplayer> MovieService::GetWatchedMoviesOfUser(const uint16_t userId, const int page, const int nmbRowsPerPage)
{
	/* SELECT watched_movie.movie_id as mid, watched_movie.user_id as uid, movie.title, genre.name FROM watched_movie
		JOIN movie ON watched_movie.movie_id = movie.id
		JOIN movie_genre ON movie.id = movie_genre.movie_id
		JOIN genre on movie_genre.genre_id = genre.id
		WHERE user_id = userId */

	int totalPages = (int) std::ceil(DatabaseManagement::GetInstance().GetStorage().count<WatchedMovie>(
		where(c(&WatchedMovie::GetUserId) == userId)) * 1.0 / nmbRowsPerPage
	);

	auto watchedMovies = DatabaseManagement::GetInstance().GetStorage().select(
		columns(&WatchedMovie::GetMovieId, &WatchedMovie::GetUserId, &WatchedMovie::GetRating, &Movie::GetTitle),
		left_join<Movie>(on(c(&Movie::GetId) == &WatchedMovie::GetMovieId)),
		where(c(&WatchedMovie::GetUserId) == userId),
		limit(nmbRowsPerPage, offset(page * nmbRowsPerPage))
	);
	std::vector<WatchedMovieDisplayer> simplifiedPageResults;
	for (auto& movieTuple : watchedMovies) {
		simplifiedPageResults.emplace_back(
			std::move(std::get<0>(movieTuple)),
			std::move(std::get<2>(movieTuple)),
			std::move(std::get<3>(movieTuple))
		);
	}
	return DBPage<WatchedMovieDisplayer>(simplifiedPageResults, totalPages, page);
}

DBPage<WishlistedMovieDisplayer> MovieService::GetWishListOfUser(const uint16_t userId, const int page, const int nmbRowsPerPage)
{
	int totalPages = std::ceil(DatabaseManagement::GetInstance().GetStorage().count<WishlistedMovie>(
		where(c(&WishlistedMovie::GetUserId) == userId)) * 1.0 / nmbRowsPerPage
	);

	auto wishList = DatabaseManagement::GetInstance().GetStorage().select(
		columns(&WishlistedMovie::GetMovieId, &WishlistedMovie::GetUserId, &Movie::GetTitle),
		left_join<Movie>(on(c(&Movie::GetId) == &WishlistedMovie::GetMovieId)),
		where(c(&WishlistedMovie::GetUserId) == userId),
		limit(nmbRowsPerPage, offset(page * nmbRowsPerPage))
	);

	std::vector<WishlistedMovieDisplayer> simplifiedPageResults;

	for (auto& movieTuple : wishList)
	{
		simplifiedPageResults.emplace_back(
			std::move(std::get<0>(movieTuple)),
			std::move(std::get<2>(movieTuple))
		);
	}

	return DBPage<WishlistedMovieDisplayer>(simplifiedPageResults, totalPages, page);
}

DBPage<Movie> MovieService::ParseRecommendedMovies(uint16_t userId, const std::vector<uint32_t>& movieIds, const int page)
{
	std::vector<uint32_t> watchedMoviesIds = GetAllWatchedMoviesIdsOfUser(userId);
	std::vector<Movie> recommendedMovies;
	for (const uint32_t& recommendedMovieId : movieIds)
	{
		if (!std::any_of(watchedMoviesIds.begin(), watchedMoviesIds.end(), [&recommendedMovieId](const uint32_t watchedMovieId) {
			return watchedMovieId == recommendedMovieId; } )) {
			Movie movie = DatabaseManagement::GetInstance().GetElementById<Movie>(recommendedMovieId);
			recommendedMovies.push_back(std::move(movie));
		}
	}
	return DBPage<Movie>(recommendedMovies, DBPage<Movie>::NMB_PAGES_VALUE_NOT_NUMBERED, page);
}

MovieInformationDisplayer MovieService::GetMovieInformations(const uint32_t id)
{
	/*
	SELECT *  movie.title, movie.release_year, genre.name FROM movie
	JOIN movie_genre on movie_genre.movie_id = movie.id
	JOIN genre on movie_genre.genre_id = genre.id
	WHERE movie.id = id
	*/
	auto informationRows = DatabaseManagement::GetInstance().GetStorage().select(
		columns(&Movie::GetTitle, &Movie::GetReleaseYear, &Genre::GetName),
		left_join<MovieGenre>(on(c(&MovieGenre::GetMovieId) == &Movie::GetId)),
		left_join<Genre>(on(c(&Genre::GetId) == &MovieGenre::GetGenreId)),
		where(c(&Movie::GetId) == id)
	);
	MovieInformationDisplayer movieInfoDisplayer(id, std::get<0>(informationRows[0]), std::get<1>(informationRows[0]));
	for (auto& row : informationRows) {
		movieInfoDisplayer.AddGenre(std::move(std::get<2>(row)));
	}
	return movieInfoDisplayer;
}

void MovieService::AddMovieToWatchlist(const uint16_t userId, const uint32_t movieId, const float rating)
{
	WatchedMovie watchedMovie(userId, movieId, rating);
	AuthService::UpdateRecomMoviesForCurrentUser(movieId, rating);
	DatabaseManagement::GetInstance().GetStorage().replace<WatchedMovie>(watchedMovie);
}

void MovieService::RemoveMovieFromWatchlist(const uint16_t userId, const uint32_t movieId)
{
	DatabaseManagement::GetInstance().GetStorage().remove<WatchedMovie>(userId, movieId);
}

void MovieService::AddMovieToWishlist(const uint16_t userId, const uint32_t movieId)
{
	WishlistedMovie wishlistMovie(userId, movieId);
	DatabaseManagement::GetInstance().GetStorage().replace<WishlistedMovie>(wishlistMovie);
}

void MovieService::RemoveMovieFromWishlist(const uint16_t userId, const uint32_t movieId)
{
	DatabaseManagement::GetInstance().GetStorage().remove<WishlistedMovie>(userId, movieId);
}

void MovieService::MoveMovieFromWishlistToWatched(const uint16_t userId, const uint32_t movieId, const float rating)
{
	WatchedMovie watchedMovie(userId, movieId, rating);
	DatabaseManagement::GetInstance().GetStorage().begin_transaction();
	try {
		DatabaseManagement::GetInstance().GetStorage().replace(watchedMovie);
		DatabaseManagement::GetInstance().GetStorage().remove<WishlistedMovie>(userId, movieId);
		DatabaseManagement::GetInstance().GetStorage().commit();
	}
	catch (std::exception e) {
		DatabaseManagement::GetInstance().GetStorage().rollback();
		throw e;
	}
}

std::vector<uint32_t> MovieService::GetAllWatchedMoviesIdsOfUser(const uint16_t userId)
{
	auto watchedMovies = DatabaseManagement::GetInstance().GetStorage().select(
		columns(&WatchedMovie::GetMovieId),
		left_join<Movie>(on(c(&Movie::GetId) == &WatchedMovie::GetMovieId)),
		where(c(&WatchedMovie::GetUserId) == userId)
	);
	std::vector<uint32_t> watchedMoviestIds;
	for (auto& movieTuple : watchedMovies) {
		watchedMoviestIds.emplace_back(
			std::move(std::get<0>(movieTuple))
		);
	}
	return watchedMoviestIds;
}
