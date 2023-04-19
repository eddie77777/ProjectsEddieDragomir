#include <gtest/gtest.h>
#include <Movie.h>

TEST(MovieTests, MovieTest) {
	Movie movie(1, "title", 1995);
	EXPECT_EQ(movie.GetId(), 1);
	EXPECT_STREQ(movie.GetTitle().c_str(), "title");
	EXPECT_EQ(movie.GetReleaseYear(), 1995);
}

TEST(MovieTests, ConstructorCopy) {
	Movie movie(1, "title", 1995);
	Movie cpy(movie);
	EXPECT_EQ(cpy.GetId(), 1);
	EXPECT_STREQ(cpy.GetTitle().c_str(), "title");
	EXPECT_EQ(cpy.GetReleaseYear(), 1995);
}

TEST(MovieTests, CopyOperator) {
	Movie movie(1, "title", 1995);
	Movie m2;
	m2 = movie;
	EXPECT_EQ(m2.GetId(), 1);
	EXPECT_STREQ(m2.GetTitle().c_str(), "title");
	EXPECT_EQ(m2.GetReleaseYear(), 1995);
}

TEST(MovieTests, MoveOperator) {
	Movie movie(1, "title", 1995);
	Movie m2=std::move(movie);

	EXPECT_EQ(m2.GetId(), 1);
	EXPECT_STREQ(m2.GetTitle().c_str(), "title");
	EXPECT_EQ(m2.GetReleaseYear(), 1995);

	EXPECT_STREQ(movie.GetTitle().c_str(), "");
}

TEST(MovieTests, MoveConstructor) {
	Movie movie(1, "title", 1995);
	Movie m2{ std::move(movie) };

	EXPECT_EQ(m2.GetId(), 1);
	EXPECT_STREQ(m2.GetTitle().c_str(), "title");
	EXPECT_EQ(m2.GetReleaseYear(), 1995);

	EXPECT_STREQ(movie.GetTitle().c_str(), "");
}


TEST(MovieTests, SetterId)
{
	Movie movie;
	movie.SetId(1);
	EXPECT_EQ(movie.GetId(), 1);
}

TEST(MovieTests, SetterTitle)
{
	Movie movie;
	movie.SetTitle("title");
	EXPECT_STREQ(movie.GetTitle().c_str(), "title");
}

TEST(MovieTests, SetterReleaseYear)
{
	Movie movie;
	movie.SetReleaseYear(1995);
	EXPECT_EQ(movie.GetReleaseYear(), 1995);
}

TEST(MovieTests, WriteOperator) {
	Movie movie(1, "title", 1995);
	std::ostringstream sstr;
	sstr << movie;
	EXPECT_STREQ(sstr.str().c_str(), "1 title");
}

//TEST(MovieTests, MovieParseData)
//{
//	Movie movie;
//	movie.ParseMovieData();
//}