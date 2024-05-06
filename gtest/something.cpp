#include <gtest/gtest.h>

#include "string.hpp"

TEST(StringFunction, strlen) {
    EXPECT_EQ(String::strlen(""), 0);
    EXPECT_EQ(String::strlen("foo"), 3);
}

TEST(StringFunction, strcpy) {
    char result[10];
    EXPECT_EQ(String::strcpy(result, "foo"), result);
    EXPECT_STREQ(result, "foo");

    EXPECT_EQ(String::strcpy(result, "a"), result);
    EXPECT_STREQ(result, "a");

    EXPECT_EQ(String::strcpy(result, ""), result);
    EXPECT_STREQ(result, "");
}

TEST(StringFunction, strncpy) {
	char result[10];
	char bisque[8];
	EXPECT_EQ(String::strncpy(result, "ferrari", 100), result);
	EXPECT_STREQ(result, "ferrari");
	EXPECT_EQ(String::strlen(result), 7);
	EXPECT_EQ(String::strncpy(result, "ferrari", 4), result);
	EXPECT_STREQ(result, "ferr");
    EXPECT_EQ(String::strlen(result), 4);
	EXPECT_EQ(String::strncpy(bisque, "lobster", 200), bisque);
	EXPECT_STREQ(bisque, "lobster");
	EXPECT_EQ(String::strlen(bisque), 7);
}

TEST(StringFunction, strcat) {
	char result[40];
	String::strcpy(result, "atomic");
    EXPECT_EQ(String::strcat(result, "mushroom"), result);
	EXPECT_STREQ(result, "atomicmushroom");
	EXPECT_EQ(String::strlen(result), 14);
}

TEST(StringFunction, strncat) {
	char result1[30];
	char result2[20];
	char result3[10];
	char result4[60];
	strcpy(result1, "pedro");
	strcpy(result2, "ramirez");
