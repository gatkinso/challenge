#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "hasher.h"

using namespace exagent;

TEST(HasherTest, MD5)
{
    std::string result;
    std::string data("{ \"request\": { \"timestamp\":\"1554584055\"} }");

    std::string expected("891f7e5b8b91ebf3eaf4523af9608594");
    
    bool ret = Hasher::md5(data, result);
    ASSERT_TRUE(ret);
    ASSERT_EQ(result, expected);
}

TEST(HasherTest, MD5Fail_Empty)
{
    std::string result;
    std::string data;                                     
    
    bool ret = Hasher::md5(data, result);
    ASSERT_FALSE(ret);
}
