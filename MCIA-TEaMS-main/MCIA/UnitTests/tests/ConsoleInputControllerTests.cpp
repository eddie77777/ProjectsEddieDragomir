#include <gtest/gtest.h>
#include <ConsoleInputController.h>
#include <sstream>
#include <WatchedMovieDisplayer.h>

template<typename T>
void gatherMovieIdSizeInpage(const std::vector<T>& page)
{
	ConsoleInputController cic;

	/* expects invalidId due to size, read the next id that exists in page & in db */
	std::string userInput("12345678910 1 2");
	std::string expectedOutput;
	expectedOutput.append(cic.OUT_PICK_ID);
	expectedOutput.append(cic.OUT_ASK_VALID_ID);

	std::istringstream inputStream(userInput);
	std::ostringstream outputStream;

	int validId = cic.gatherMovieIdFromUser(page, true, outputStream, inputStream);
	EXPECT_EQ(validId, 1);
	EXPECT_STREQ(outputStream.str().c_str(), expectedOutput.c_str());
}

template<typename T>
void gatherMovieIdStoiNotPage(const std::vector<T>& page)
{
	ConsoleInputController cic;

	/* expects invalidId due to stoi exception, id 2 not in page but is valid */
	std::string userInput("s 2 y 1");
	std::string expectedOutput;
	expectedOutput.append(cic.OUT_PICK_ID);
	expectedOutput.append(cic.OUT_ASK_VALID_ID);
	expectedOutput.append(cic.OUT_ID_NOT_IN_PAGE_CONFIRM);

	std::istringstream inputStream(userInput);
	std::ostringstream outputStream;

	int validId = cic.gatherMovieIdFromUser(page, true, outputStream, inputStream);
	EXPECT_EQ(validId, 2);
	EXPECT_STREQ(outputStream.str().c_str(), expectedOutput.c_str());
}

template<typename T>
void gatherMovieIdInvalidId(const std::vector<T>& page)
{
	ConsoleInputController cic;

	/* expects invalidId due to id not in page or in db */
	std::string userInput("-1 y 1 4");
	std::string expectedOutput;
	expectedOutput.append(cic.OUT_PICK_ID);
	expectedOutput.append(cic.OUT_ID_NOT_IN_PAGE_CONFIRM);
	expectedOutput.append(cic.OUT_ASK_VALID_ID);

	std::istringstream inputStream(userInput);  
	std::ostringstream outputStream;

	int validId = cic.gatherMovieIdFromUser(page, true, outputStream, inputStream);
	EXPECT_EQ(validId, 1);
	EXPECT_STREQ(outputStream.str().c_str(), expectedOutput.c_str());
}

TEST(ConsoleInputControllerTests, GatherMovieIdSizeInpage_General) {
	std::vector<WatchedMovieDisplayer> moviesInPage;
	moviesInPage.emplace_back(1, 5.0, "TestTitle");
	gatherMovieIdSizeInpage(moviesInPage);
}

TEST(ConsoleInputControllerTests, GatherMovieIdSizeInpage_Specialized) {
	std::vector<Movie> moviesInPage;
	moviesInPage.emplace_back(1, "TestTitle", 2000);
	gatherMovieIdSizeInpage(moviesInPage);
}

TEST(ConsoleInputControllerTests, GatherMovieIdlStoiNotPage_General) {
	std::vector<WatchedMovieDisplayer> moviesInPage;
	moviesInPage.emplace_back(1, 5.0, "TestTitle");
	gatherMovieIdStoiNotPage(moviesInPage);
}

TEST(ConsoleInputControllerTests, GatherMovieIdStoiNotPage_Specialized) {
	std::vector<Movie> moviesInPage;
	moviesInPage.emplace_back(1, "TestTitle", 2000);
	gatherMovieIdStoiNotPage(moviesInPage);
}

TEST(ConsoleInputControllerTests, GatherMovieIdInvalidId_General) {
	std::vector<WatchedMovieDisplayer> moviesInPage;
	moviesInPage.emplace_back(1, 5.0, "TestTitle");
	gatherMovieIdInvalidId(moviesInPage);
}


TEST(ConsoleInputControllerTests, GatherMovieIdInvalidId_Specialized) {
	std::vector<Movie> moviesInPage;
	moviesInPage.emplace_back(1, "TestTitle", 2000);
	gatherMovieIdInvalidId(moviesInPage);
}

TEST(ConsoleInputControllerTests, GatherMovieRatingInfo) {
	std::vector<Movie> moviesInPage;
	moviesInPage.emplace_back(1, "TestTitle", 2000);
	ConsoleInputController cic;

	/* input valid id from start; 
	- try with rating longer than maximumValueLength
	- try with rating not convertable to float
	- try with rating not within [1.0, 5.0]
	- go with valid rating */
	std::string userInput("1 1234 f12 0.0 4.5");
	std::string expectedOutput;
	expectedOutput.append(cic.OUT_PICK_ID);
	expectedOutput.append(cic.OUT_PICK_RATING);
	expectedOutput.append(cic.OUT_RATING_OUT_OF_RANGE);
	expectedOutput.append(cic.OUT_RATING_OUT_OF_RANGE);
	expectedOutput.append(cic.OUT_RATING_OUT_OF_RANGE);

	std::istringstream inputStream(userInput);
	std::ostringstream outputStream;

	std::pair<int, float> movieRating = cic.gatherMovieRatingInfo(moviesInPage, true, outputStream, inputStream);
	EXPECT_EQ(movieRating.first, 1);
	EXPECT_STREQ(outputStream.str().c_str(), expectedOutput.c_str());
}