#include <gtest/gtest.h>
#include <WishlistedMovieDisplayer.h>

TEST(WishlistedMovieDisplayerTests, Constructor)
{
	WishlistedMovieDisplayer wld(1, "title");
	EXPECT_EQ(wld.GetMovieId(), 1);
}

TEST(WishlistedMovieDisplayerTests, WriteOperator)
{
	WishlistedMovieDisplayer wld(1, "title");
	std::ostringstream sstr;
	sstr << wld;
	EXPECT_STREQ(sstr.str().c_str(), "1 title");
}

