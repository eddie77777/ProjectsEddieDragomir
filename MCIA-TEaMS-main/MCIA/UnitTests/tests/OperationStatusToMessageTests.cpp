#include <gtest/gtest.h>
#include <OperationStatusToMessage.h>

TEST(OperationStatusToMessageTests, GetMessageBlank) {
	OperationStatusToMessage ostm;
	std::string result = ostm.GetMessage(OperationStatus::Code::F_BLANK, "modfield");
	EXPECT_STREQ(result.c_str(), "Field modfield cannot be left blank.");

	result = ostm.GetMessage(OperationStatus::Code::F_BLANK, 1);
	EXPECT_STREQ(result.c_str(), "Field 1 cannot be left blank.");

	result = ostm.GetMessage(OperationStatus::Code::F_BLANK, "modfield", "useless", 4);
	EXPECT_STREQ(result.c_str(), "Field modfield cannot be left blank.");
}

TEST(OperationStatusToMessageTests, GetMessageSize) {
	OperationStatusToMessage ostm;
	std::string result = ostm.GetMessage(OperationStatus::Code::F_SIZE, "modfield", 5);
	EXPECT_STREQ(result.c_str(), "Field modfield must be longer than 5 characters.");

	result = ostm.GetMessage(OperationStatus::Code::F_SIZE, "modfield");
	EXPECT_STREQ(result.c_str(), "Field modfield must be longer than % characters.");

	result = ostm.GetMessage(OperationStatus::Code::F_SIZE, "modfield", 5, 10, "useless");
	EXPECT_STREQ(result.c_str(), "Field modfield must be longer than 5 characters.");
}

TEST(OperationStatusToMessageTests, GetMessageAlphaNumeric) {
	OperationStatusToMessage ostm;
	std::string result = ostm.GetMessage(OperationStatus::Code::F_ALPHA_NUMERIC, "modfield", "dots");
	EXPECT_STREQ(result.c_str(), "Field modfield must only contain dots.");
}

TEST(OperationStatusToMessageTests, GetMessageTrim) {
	OperationStatusToMessage ostm;
	std::string result = ostm.GetMessage(OperationStatus::Code::F_TRIM, "modfield");
	EXPECT_STREQ(result.c_str(), "Trailing whitespaces are not allowed in modfield.");
}