#include <gtest/gtest.h>
#include <DBValidation.h>

TEST(DBValidationTests, UsernameBlank) {
	DBValidation validator;
	std::string username("      ");
	OperationStatus result = validator.IsUsernameValid(username);
	EXPECT_EQ(result.GetCode(), OperationStatus::Code::F_BLANK);
}

TEST(DBValidationTests, UsernameNotTrimmed) {
	DBValidation validator;
	std::string username("  username  ");
	OperationStatus result = validator.IsUsernameValid(username);
	EXPECT_EQ(result.GetCode(), OperationStatus::Code::F_TRIM);
}

TEST(DBValidationTests, UsernameSize) {
	DBValidation validator;
	std::string username("a");
	OperationStatus result = validator.IsUsernameValid(username);
	EXPECT_EQ(result.GetCode(), OperationStatus::Code::F_SIZE);
}

TEST(DBValidationTests, UsernameAlphaNumeric) {
	DBValidation validator;
	std::string username("_aaa");
	OperationStatus result = validator.IsUsernameValid(username);
	EXPECT_EQ(result.GetCode(), OperationStatus::Code::F_ALPHA_NUMERIC);
	username = "a;$";
	result = validator.IsUsernameValid(username);
	EXPECT_EQ(result.GetCode(), OperationStatus::Code::F_ALPHA_NUMERIC);
}

TEST(DBValidationTests, UsernameValid) {
	DBValidation validator;
	std::string username("userna13e_");
	OperationStatus result = validator.IsUsernameValid(username);
	EXPECT_EQ(result.GetCode(), OperationStatus::Code::SUCCESS);
}

TEST(DBValidationTests, PasswordBlank) {
	DBValidation validator;
	std::string password("      ");
	OperationStatus result = validator.IsPasswordValid(password);
	EXPECT_EQ(result.GetCode(), OperationStatus::Code::F_BLANK);
}

TEST(DBValidationTests, PasswordSize) {
	DBValidation validator;
	std::string password("12");
	OperationStatus result = validator.IsPasswordValid(password);
	EXPECT_EQ(result.GetCode(), OperationStatus::Code::F_SIZE);
}

TEST(DBValidationTests, PasswordRegex) {
	DBValidation validator;
	std::string password("a12");
	OperationStatus result = validator.IsPasswordValid(password);
	EXPECT_EQ(result.GetCode(), OperationStatus::Code::F_INVALID_PATTERN);
	
	result = validator.IsPasswordValid("aaa@!");
	EXPECT_EQ(result.GetCode(), OperationStatus::Code::F_INVALID_PATTERN);

	result = validator.IsPasswordValid("aaaaa");
	EXPECT_EQ(result.GetCode(), OperationStatus::Code::F_INVALID_PATTERN);

	result = validator.IsPasswordValid("!!!!");
	EXPECT_EQ(result.GetCode(), OperationStatus::Code::F_INVALID_PATTERN);

	result = validator.IsPasswordValid("11111");
	EXPECT_EQ(result.GetCode(), OperationStatus::Code::F_INVALID_PATTERN);
}


TEST(DBValidationTests, PasswordValid) {
	DBValidation validator;
	std::string password("parola!1");
	OperationStatus result = validator.IsPasswordValid(password);
	EXPECT_EQ(result.GetCode(), OperationStatus::Code::SUCCESS);
}

TEST(DBValidationTests, UsernameErrorMessage) {
	DBValidation validator;
	EXPECT_STREQ(validator.UsernameErrorMessage(OperationStatus::Code::F_BLANK).c_str(),
		"Field username cannot be left blank.");
	EXPECT_STREQ(validator.UsernameErrorMessage(OperationStatus::Code::F_TRIM).c_str(),
		"Trailing whitespaces are not allowed in username.");
	EXPECT_STREQ(validator.UsernameErrorMessage(OperationStatus::Code::F_SIZE).c_str(),
		"Field username must be longer than 3 characters.");
	EXPECT_STREQ(validator.UsernameErrorMessage(OperationStatus::Code::F_ALPHA_NUMERIC).c_str(),
		"Field username must only contain alpha-numeric characters and must not begin with a digit.");
	EXPECT_STREQ(validator.UsernameErrorMessage(OperationStatus::Code::SUCCESS).c_str(),
		"");
}

TEST(DBValidationTests, PasswordErrorMessage) {
	DBValidation validator;
	EXPECT_STREQ(validator.PasswordErrorMessage(OperationStatus::Code::F_BLANK).c_str(),
		"Field password cannot be left blank.");
	EXPECT_STREQ(validator.PasswordErrorMessage(OperationStatus::Code::F_SIZE).c_str(),
		"Field password must be longer than 3 characters.");
	EXPECT_STREQ(validator.PasswordErrorMessage(OperationStatus::Code::F_INVALID_PATTERN).c_str(),
		"Invalid pattern. Field password must contain at least:\n- one digit; \n- one letter; \n- one special character (!@#$%^&*).");
	EXPECT_STREQ(validator.PasswordErrorMessage(OperationStatus::Code::SUCCESS).c_str(),
		"");

}