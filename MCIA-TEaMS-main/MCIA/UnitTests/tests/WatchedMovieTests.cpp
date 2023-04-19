#include <gtest/gtest.h>
#include <WatchedMovie.h>

TEST(WatchedMovieTests, WatchedMovieTests)
{
	WatchedMovie watchedMovie(1, 2, 3.5);
	EXPECT_EQ(watchedMovie.GetUserId(), 1);
	EXPECT_EQ(watchedMovie.GetMovieId(), 2);
	EXPECT_EQ(watchedMovie.GetRating(), 3.5);
}

TEST(WatchedMovieTests, SetterUserId)
{
	WatchedMovie watchedMovie;
	watchedMovie.SetUserId(1);
	EXPECT_EQ(watchedMovie.GetUserId(), 1);
}

TEST(WatchedMovieTests, SetterMovieId)
{
	WatchedMovie watchedMovie;
	watchedMovie.SetMovieId(1);
	EXPECT_EQ(watchedMovie.GetMovieId(), 1);
}

TEST(WatchedMovieTests, SetterRating)
{
	WatchedMovie watchedMovie;
	watchedMovie.SetRating(1.0);
	EXPECT_EQ(watchedMovie.GetRating(), 1.0);
}
