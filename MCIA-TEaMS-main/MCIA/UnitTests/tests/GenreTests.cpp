#include <gtest/gtest.h>
#include <Genre.h>

TEST(GenreTests, GenreTestNoId) {
	Genre genre("nume");
	EXPECT_EQ(genre.GetId(), 0);
	EXPECT_STREQ(genre.GetName().c_str(),"nume");
}

TEST(GenreTests, GenreTest) {
	Genre genre(1,"nume");
	EXPECT_EQ(genre.GetId(), 1);
	EXPECT_STREQ(genre.GetName().c_str(), "nume");
}

TEST(GenreTests, SetterId)
{
	Genre genre;
	genre.SetId(1);
	EXPECT_EQ(genre.GetId(), 1);
}

TEST(GenreTests, SetterName)
{
	Genre genre;
	genre.SetName("nume");
	EXPECT_STREQ(genre.GetName().c_str(), "nume");
}

//TEST(GenreTests, SetterName)
//{
//	Genre genre;
//	genre.ParseGenres();
//}



