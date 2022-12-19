#include "gtest/gtest.h"
#include "jago/JagoUtils.h"

#include <string>
#include <vector>

TEST(JagoUtilsTest, StringEqual) {
    std::string str1 = "a";
    std::string str2 = "ab";
    std::string str3 = "\n\t ";
    std::string str4;
    std::string str5 = "abcdef1234";
    std::string str6 = "abcdef12345";

    EXPECT_FALSE(Jago::StringEquals(str1, str2));
    EXPECT_FALSE(Jago::StringEquals(str1, str3));
    EXPECT_FALSE(Jago::StringEquals(str1, str4));
    EXPECT_FALSE(Jago::StringEquals(str1, str5));
    EXPECT_FALSE(Jago::StringEquals(str1, str6));

    EXPECT_TRUE(Jago::StringEquals(str1, str1));
    EXPECT_TRUE(Jago::StringEquals(str2, str2));
    EXPECT_TRUE(Jago::StringEquals(str3, str3));
    EXPECT_TRUE(Jago::StringEquals(str4, str4));
    EXPECT_TRUE(Jago::StringEquals(str5, str5));
    EXPECT_TRUE(Jago::StringEquals(str6, str6));
}

TEST(JagoUtilsTest, IsNumber) {
    EXPECT_TRUE(Jago::IsNumber('0'));
    EXPECT_TRUE(Jago::IsNumber('1'));
    EXPECT_TRUE(Jago::IsNumber('2'));
    EXPECT_TRUE(Jago::IsNumber('3'));
    EXPECT_TRUE(Jago::IsNumber('4'));
    EXPECT_TRUE(Jago::IsNumber('5'));
    EXPECT_TRUE(Jago::IsNumber('6'));
    EXPECT_TRUE(Jago::IsNumber('7'));
    EXPECT_TRUE(Jago::IsNumber('8'));
    EXPECT_TRUE(Jago::IsNumber('9'));

    EXPECT_FALSE(Jago::IsNumber(0));
    EXPECT_FALSE(Jago::IsNumber(10));
    EXPECT_FALSE(Jago::IsNumber(30));
    EXPECT_FALSE(Jago::IsNumber('A'));
    EXPECT_FALSE(Jago::IsNumber('B'));
    EXPECT_FALSE(Jago::IsNumber('C'));
    EXPECT_FALSE(Jago::IsNumber('a'));
    EXPECT_FALSE(Jago::IsNumber('b'));
    EXPECT_FALSE(Jago::IsNumber('c'));
    EXPECT_FALSE(Jago::IsNumber(';'));
}

#define NOT_FOUND -1
TEST(JagoUtilsTest, VectorBinarySearch) {
    std::vector chars1 = {'a', 'b', 'c', 'd', 'e', 'f', 'g'};
    std::vector chars2 = {'c', 'd', 'e'};
    std::vector chars3 = (std::initializer_list<char>) {};

    EXPECT_EQ(Jago::BinarySearch(chars1, 'a'), 0);
    EXPECT_EQ(Jago::BinarySearch(chars1, 'b'), 1);
    EXPECT_EQ(Jago::BinarySearch(chars1, 'c'), 2);
    EXPECT_EQ(Jago::BinarySearch(chars1, 'd'), 3);
    EXPECT_EQ(Jago::BinarySearch(chars1, 'e'), 4);
    EXPECT_EQ(Jago::BinarySearch(chars1, 'f'), 5);
    EXPECT_EQ(Jago::BinarySearch(chars1, 'g'), 6);

    EXPECT_EQ(Jago::BinarySearch(chars2, 'a'), NOT_FOUND);
    EXPECT_EQ(Jago::BinarySearch(chars2, 'b'), NOT_FOUND);
    EXPECT_EQ(Jago::BinarySearch(chars2, 'c'), 0);
    EXPECT_EQ(Jago::BinarySearch(chars2, 'd'), 1);
    EXPECT_EQ(Jago::BinarySearch(chars2, 'e'), 2);
    EXPECT_EQ(Jago::BinarySearch(chars2, 'f'), NOT_FOUND);
    EXPECT_EQ(Jago::BinarySearch(chars2, 'g'), NOT_FOUND);

    EXPECT_EQ(Jago::BinarySearch(chars3, 'a'), NOT_FOUND);
    EXPECT_EQ(Jago::BinarySearch(chars3, 'b'), NOT_FOUND);
    EXPECT_EQ(Jago::BinarySearch(chars3, 'c'), NOT_FOUND);
    EXPECT_EQ(Jago::BinarySearch(chars3, 'd'), NOT_FOUND);
    EXPECT_EQ(Jago::BinarySearch(chars3, 'e'), NOT_FOUND);
    EXPECT_EQ(Jago::BinarySearch(chars3, 'f'), NOT_FOUND);
    EXPECT_EQ(Jago::BinarySearch(chars3, 'g'), NOT_FOUND);
}
#undef NOT_FOUND