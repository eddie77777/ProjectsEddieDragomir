#include <gtest/gtest.h>
#include <WishlistedMovie.h>

TEST(WishlistedMovieTests, Constructor)
{
	WishlistedMovie wishList(1, 2);
	EXPECT_EQ(wishList.GetUserId(), 1);
	EXPECT_EQ(wishList.GetMovieId(), 2);
}

TEST(WishlistedMovieTests, SetterUserId)
{
	WishlistedMovie wishList;
	wishList.SetUserId(1);
	EXPECT_EQ(wishList.GetUserId(), 1);
}

TEST(WishlistedMovieTests, SetterMovieId)
{
	WishlistedMovie wishList;
	wishList.SetMovieId(1);
	EXPECT_EQ(wishList.GetMovieId(), 1);
}
