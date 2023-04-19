#include <gtest/gtest.h>
#include <MovieInformationDisplayer.h>

TEST(MovieInformationDisplayerTests, Constructor) {
	MovieInformationDisplayer mvd(1, "titlu", 2002, "genuri");
	EXPECT_EQ(mvd.GetMovieId(), 1);
	EXPECT_EQ(mvd.GetTitle(), "titlu");
	EXPECT_EQ(mvd.GetReleaseYear(), 2002);
	EXPECT_EQ(mvd.GetGenres(), "genuri");
}

TEST(MovieInformationDisplayerTests, GetterMovieId) {
	MovieInformationDisplayer mvd(3, "titlu", 2002, "genuri");
	EXPECT_EQ(mvd.GetMovieId(), 3);
}

TEST(MovieInformationDisplayerTests, GetterTitle) {
	MovieInformationDisplayer mvd(3, "Titlu film", 2002, "genuri");
	EXPECT_STREQ(mvd.GetTitle().c_str(), "Titlu film");
}

TEST(MovieInformationDisplayerTests, GetterReleaseYear) {
	MovieInformationDisplayer mvd(3, "titlu", 2002, "genuri");
	EXPECT_EQ(mvd.GetReleaseYear(), 2002);
}

TEST(MovieInformationDisplayerTests, GetterGenres) {
	MovieInformationDisplayer mvd(3, "titlu", 2002, "gen, gen1");
	EXPECT_EQ(mvd.GetGenres(), "gen, gen1");
}

TEST(MovieInformationDisplayerTests, AddGenre) {
	MovieInformationDisplayer mvd(3, "titlu", 2002);
	EXPECT_STREQ(mvd.GetGenres().c_str(), "");
	mvd.AddGenre("gen1");
	mvd.AddGenre("gen2");
	EXPECT_STREQ(mvd.GetGenres().c_str(), "gen1, gen2");
}
