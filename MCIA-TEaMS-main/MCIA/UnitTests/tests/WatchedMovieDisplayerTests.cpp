#include <gtest/gtest.h>
#include <WatchedMovieDisplayer.h>

TEST(WatchedMovieDisplayerTests, WatchedMovieDisplayerTest)
{
	WatchedMovieDisplayer wmd(1, 2.0, "title");
	EXPECT_EQ(wmd.GetMovieId(), 1);
}

TEST(WatchedMovieDisplayerTests, WriteOperator)
{
	WatchedMovieDisplayer wmd(1, 2.0, "title");
	std::ostringstream sstr;
	sstr << wmd;
	EXPECT_STREQ(sstr.str().c_str(), "1 title 2.0/5.0");
}