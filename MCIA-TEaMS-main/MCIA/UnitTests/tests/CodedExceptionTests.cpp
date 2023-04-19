#include <gtest/gtest.h>
#include <CodedException.h>

TEST(CodedExceptionTests, ConstructorCharChar) {
	CodedException e("Valid", "mesaj");
	EXPECT_STREQ(e.what(), "[Valid]mesaj");
}

TEST(CodedExceptionTests, ConstructorOpStatusString) {
	CodedException e(OperationStatus::F_SIZE, "mesaj");
	EXPECT_STREQ(std::string(e.GetWhat()).c_str(), "[Size]mesaj");
}

TEST(CodedExceptionTests, GetterCode) {
	CodedException e(OperationStatus::F_SIZE, "mesaj");
	EXPECT_EQ(e.GetCode(), OperationStatus::F_SIZE);
}

TEST(CodedExceptionTests, GetterMessage) {
	CodedException e(OperationStatus::F_SIZE, "mesaj");
	EXPECT_STREQ(e.GetMessage().c_str(), "mesaj");
}

TEST(CodedExceptionTests, GetterWhat) {
	CodedException e("Valid", "mesaj");
	EXPECT_STREQ(e.GetWhat().c_str(), "[Valid]mesaj");
}

TEST(CodedExceptionTests, What) {
	CodedException e("Valid", "mesaj");
	EXPECT_STREQ(e.what(), "[Valid]mesaj");
}