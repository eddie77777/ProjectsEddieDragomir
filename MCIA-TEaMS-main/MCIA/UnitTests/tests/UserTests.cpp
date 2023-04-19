#include <gtest/gtest.h>
#include <User.h>

TEST(UserTests, UserTest) {
	User user(1, "nume", "parola");
	EXPECT_EQ(user.GetId(), 1);
	EXPECT_STREQ(user.GetName().c_str(), "nume");
	EXPECT_STREQ(user.GetPassword().c_str(), "parola");
}

TEST(UserTests, ConstructorCopy) {
	User user(1, "nume", "parola");
	User cpy(user);
	EXPECT_EQ(cpy.GetId(), 1);
	EXPECT_STREQ(cpy.GetName().c_str(), "nume");
	EXPECT_STREQ(cpy.GetPassword().c_str(), "parola");
}

TEST(UserTests, ConstructorNoId) {
	User user("nume", "parola");
	EXPECT_EQ(user.GetId(), 0);
	EXPECT_STREQ(user.GetName().c_str(), "nume");
	EXPECT_STREQ(user.GetPassword().c_str(), "parola");
}

TEST(UserTests, CopyOperator) {
	User user(1, "nume", "parola");
	User u2;
	u2 = user;
	EXPECT_EQ(u2.GetId(), 1);
	EXPECT_STREQ(u2.GetName().c_str(), "nume");
	EXPECT_STREQ(u2.GetPassword().c_str(), "parola");
}

TEST(UserTests, MoveOperator) {
	User user(1, "nume", "parola");
	User u2 = std::move(user);

	EXPECT_EQ(u2.GetId(), 1);
	EXPECT_STREQ(u2.GetName().c_str(), "nume");
	EXPECT_STREQ(u2.GetPassword().c_str(), "parola");
	EXPECT_EQ(user.GetName(), "");
	EXPECT_EQ(user.GetPassword(), "");
}

TEST(UserTests, MoveConstructor) {
	User user(1, "nume", "parola");
	User u2{ std::move(user) };

	EXPECT_EQ(u2.GetId(), 1);
	EXPECT_STREQ(u2.GetName().c_str(), "nume");
	EXPECT_STREQ(u2.GetPassword().c_str(), "parola");
	EXPECT_EQ(user.GetName(), "");
	EXPECT_EQ(user.GetPassword(), "");
}

TEST(UserTests, SetterName) {
	User user;
	user.SetName("username");
	EXPECT_STREQ(user.GetName().c_str(), "username");
}

TEST(UserTests, SetterPassword) {
	User user;
	user.SetPassword("password");
	EXPECT_STREQ(user.GetPassword().c_str(), "password");
}

TEST(UserTests, SetterId) {
	User user;
	user.SetId(1);
	EXPECT_EQ(user.GetId(), 1);
}

TEST(UserTests, WriteOperator) {
	User user(1, "nume", "parola");
	std::ostringstream sstr;
	sstr << user;
	EXPECT_STREQ(sstr.str().c_str(), "1 nume");

}