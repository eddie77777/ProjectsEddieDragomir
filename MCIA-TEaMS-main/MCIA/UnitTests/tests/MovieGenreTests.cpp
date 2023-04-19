#include <gtest/gtest.h>
#include <MovieGenre.h>

TEST(MovieGenreTests, MovieGenreTest)
{
	MovieGenre moviegenre(1, 2);
	EXPECT_EQ(moviegenre.GetMovieId(), 1);
	EXPECT_EQ(moviegenre.GetGenreId(), 2);
}

TEST(MovieGenreTests, SetterGenreId)
{
	MovieGenre moviegenre;
	moviegenre.SetGenreId(1);
	EXPECT_EQ(moviegenre.GetGenreId(), 1);
}

TEST(MovieGenreTests, SetterMovieId)
{
	MovieGenre moviegenre;
	moviegenre.SetMovieId(1);
	EXPECT_EQ(moviegenre.GetMovieId(), 1);
}

//TEST(MovieGenreTests, LinkedGenreMovie)
//{
//	MovieGenre moviegenre;
//	moviegenre.LinkGenreMovie();
//}