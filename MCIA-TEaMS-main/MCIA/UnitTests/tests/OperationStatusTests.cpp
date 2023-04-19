#include <gtest/gtest.h>
#include <OperationStatus.h>

using OpCode = OperationStatus::Code;

TEST(OperationStatusTests, CodeConstructor) {
	OperationStatus o(OpCode::SUCCESS);
	EXPECT_EQ(o.GetCode(), OpCode::SUCCESS);
}

TEST(OperationStatusTests, GetterCode) {
	OperationStatus o(OpCode::F_BLANK);
	EXPECT_EQ(o.GetCode(), OpCode::F_BLANK);
}

TEST(OperationStatusTests, CodeToString) {
	EXPECT_STREQ(OperationStatus::CodeToString(OpCode::SUCCESS).c_str(), "Valid");

	EXPECT_STREQ(OperationStatus::CodeToString(OpCode::F_BLANK).c_str(), "Blank");
	EXPECT_STREQ(OperationStatus::CodeToString(OpCode::F_SIZE).c_str(), "Size");
	EXPECT_STREQ(OperationStatus::CodeToString(OpCode::F_ALPHA_NUMERIC).c_str(), "AlphaNumeric");
	EXPECT_STREQ(OperationStatus::CodeToString(OpCode::F_TRIM).c_str(), "Trim");
	EXPECT_STREQ(OperationStatus::CodeToString(OpCode::F_INVALID_PATTERN).c_str(), "InvalidPattern");

	EXPECT_STREQ(OperationStatus::CodeToString(OpCode::DB_INVALID_ENTITY).c_str(), "InvalidEntity");
	EXPECT_STREQ(OperationStatus::CodeToString(OpCode::DB_ENTITY_NOT_FOUND).c_str(), "EntityNotFound");
	EXPECT_STREQ(OperationStatus::CodeToString(OpCode::DB_USER_INVALID_PASSWORD).c_str(), "InvalidUser");
	EXPECT_STREQ(OperationStatus::CodeToString(OpCode::DB_INVALID_ID).c_str(), "InvalidId");
	
	OpCode dummyCode = static_cast<OpCode>(OpCode::COUNT+1);
	EXPECT_STREQ(OperationStatus::CodeToString(dummyCode).c_str(), "Err");
}

TEST(OperationStatusTests, CmpToOperationStatus) {
	OperationStatus o1(OpCode::F_BLANK);
	OperationStatus o2(OpCode::DB_ENTITY_NOT_FOUND);
	OperationStatus o3(OpCode::F_BLANK);

	EXPECT_EQ(o1 == o2, false);
	EXPECT_EQ(o1 != o2, true);
	EXPECT_EQ(o1 == o3, true);
	EXPECT_EQ(o1 != o3, false);
	EXPECT_EQ(o1 == o1, true);
	EXPECT_EQ(o1 != o1, false);
}

TEST(OperationStatusTests, CmpToBool) {
	OperationStatus o1(OpCode::SUCCESS);
	OperationStatus o2(OpCode::DB_ENTITY_NOT_FOUND);

	EXPECT_EQ(o1 == true, true);
	EXPECT_EQ(o1 != true, false);
	EXPECT_EQ(o2 == true, false);
	EXPECT_EQ(o2 != true, true);
}

TEST(OperationStatusTests, BoolConverter) {
	OperationStatus o(OpCode::SUCCESS);
	EXPECT_TRUE(bool(o) == true);
	for (int i = 2; i <= OpCode::COUNT; ++i) {
		OperationStatus o(static_cast<OpCode>(i));
		EXPECT_FALSE(bool(o) == true);
	}
}

TEST(OperationStatusTests, EqualOperator) {
	OperationStatus o1(OpCode::SUCCESS);
	OperationStatus o2(OpCode::F_BLANK);
	OperationStatus o3(OpCode::F_ALPHA_NUMERIC);
	o1 = o2 = o3;
	EXPECT_EQ(o1.GetCode(), o2.GetCode());
	EXPECT_EQ(o3.GetCode(), o2.GetCode());
	EXPECT_EQ(o3.GetCode(), OpCode::F_ALPHA_NUMERIC);
}

TEST(OperationStatusTests, StringConverter) {
	for (int i = 1; i <= OpCode::COUNT; ++i) {
		OperationStatus o(static_cast<OpCode>(i));
		EXPECT_STREQ(OperationStatus::CodeToString(o.GetCode()).c_str(), std::string(o).c_str());
	}
}