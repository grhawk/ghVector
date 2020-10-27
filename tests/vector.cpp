#include<gtest/gtest.h>

#include<ghVector.h>

TEST(VectorFix, CreateADummyVectorObj){
    ghds::Vector<int> vector = ghds::Vector<int>();
    ASSERT_EQ(vector.size(), 0);
    EXPECT_NO_THROW();
}

TEST(VectorFix, PushElementToVector)
{
    ghds::Vector<int> vector = ghds::Vector<int>();
    vector.push_back(5);
}

TEST(VectorFix, PushElementToVectorAndCheckSize)
{
    ghds::Vector<int> vector = ghds::Vector<int>();
    ASSERT_EQ(vector.size(), 0);
    vector.push_back(5);
    ASSERT_EQ(vector.size(), 1);
}

TEST(VectorFix, PushTwoElementsToVectorAndCheckSize)
{
    ghds::Vector<int> vector = ghds::Vector<int>();
    ASSERT_EQ(vector.size(), 0);
    vector.push_back(5);
    ASSERT_EQ(vector.size(), 1);
    vector.push_back(5);
    ASSERT_EQ(vector.size(), 2);

}

