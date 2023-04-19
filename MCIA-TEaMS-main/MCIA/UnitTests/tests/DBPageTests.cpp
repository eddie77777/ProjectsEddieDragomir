#include <gtest/gtest.h>
#include <DBPage.h>
#include <Movie.h>

TEST(DBPageTests, DefaultConstructor) {
	DBPage<Movie> page;
	EXPECT_EQ(page.GetNmbPages(), 0);
	EXPECT_EQ(page.GetNmbCurrentPage(), 0);
	EXPECT_EQ(page.GetResults().size(), 0);
}

TEST(DBPageTests, Constructor) {
	Movie inserted(1, "Title", 2000);
	std::vector<Movie> mv;
	mv.emplace_back(inserted);

	DBPage<Movie> page(mv, 10, 1);
	EXPECT_EQ(page.GetNmbPages(), 10);
	EXPECT_EQ(page.GetNmbCurrentPage(), 1);
	EXPECT_EQ(page.GetResults().size(), 1);
	EXPECT_EQ(page.GetResults().at(0).GetId(), inserted.GetId());
}

TEST(DBPageTests, GetterResults) {
	Movie inserted(1, "Title", 2000);
	std::vector<Movie> mv;
	mv.emplace_back(inserted);
	
	DBPage<Movie> page(mv, 0, 0);
	EXPECT_EQ(page.GetResults().size(), 1);
	EXPECT_EQ(page.GetResults().at(0).GetId(), inserted.GetId());
}

TEST(DBPageTests, GetterNmbPages) {
	std::vector<Movie> mv;
	DBPage<Movie> page(mv, 10, 0);
	EXPECT_EQ(page.GetNmbPages(), 10);
}

TEST(DBPageTests, GetterCurrentPage) {
	std::vector<Movie> mv;
	DBPage<Movie> page(mv, 10, 3);
	EXPECT_EQ(page.GetNmbCurrentPage(), 3);
}