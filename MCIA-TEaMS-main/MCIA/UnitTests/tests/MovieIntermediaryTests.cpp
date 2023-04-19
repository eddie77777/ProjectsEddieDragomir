#include <gtest/gtest.h>
#include <MovieIntermediary.h>

TEST(MovieIntermediaryTests, DefaultContructor) {
	MovieIntermediary movie;
	EXPECT_EQ(movie.GetId(), 0);
	EXPECT_EQ(movie.GetTitle(), "");
	EXPECT_EQ(movie.GetGenre(), "");
}

TEST(MovieIntermediaryTests, Constructor) {
	MovieIntermediary movie(1, "titlu", "genuri");
	EXPECT_EQ(movie.GetId(), 1);
	EXPECT_EQ(movie.GetTitle(), "titlu");
	EXPECT_EQ(movie.GetGenre(), "genuri");
}

TEST(MovieIntermediaryTests, GetterId) {
	MovieIntermediary movie(1, "titlu", "genuri");
	EXPECT_EQ(movie.GetId(), 1);
}

TEST(MovieIntermediaryTests, SetterId) {
	MovieIntermediary movie;
	movie.SetId(4);
	EXPECT_EQ(movie.GetId(), 4);
}

TEST(MovieIntermediaryTests, GetterTitle) {
	MovieIntermediary movie(1, "titlu", "genuri");
	EXPECT_EQ(movie.GetTitle(), "titlu");
}

TEST(MovieIntermediaryTests, SetterTitle) {
	MovieIntermediary movie;
	movie.SetTitle("titlu");
	EXPECT_EQ(movie.GetTitle(), "titlu");
}
TEST(MovieIntermediaryTests, GetterGenre) {
	MovieIntermediary movie(1, "titlu", "genuri");
	EXPECT_EQ(movie.GetGenre(), "genuri");
}

TEST(MovieIntermediaryTests, SetterGenre) {
	MovieIntermediary movie;
	movie.SetGenre("gen");
	EXPECT_EQ(movie.GetGenre(), "gen");
}