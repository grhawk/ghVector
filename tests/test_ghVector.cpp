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

TEST(VectorFix, PushTwoElementsToVectorRetrieveThemUsingTheIndex)
{
    ghds::Vector<int> vector = ghds::Vector<int>();
    vector.push_back(1);
    vector.push_back(2);
    ASSERT_EQ(vector[0], 1);
    ASSERT_EQ(vector[1], 2);
}

TEST(VectorFix, PushTwoElementsToVectorAndChangeTheirValueAndRetrieveThemUsingTheIndex)
{
    ghds::Vector<int> vector = ghds::Vector<int>();
    vector.push_back(1);
    vector.push_back(2);
    vector[0] = 10;
    vector[1] = 20;
    ASSERT_EQ(vector[0], 10);
    ASSERT_EQ(vector[1], 20);
}

TEST(VectorFix, PushTwoElementsAndInsertOneInBetweenCheckCapacityIncreases)
{
    ghds::Vector<int> vector = ghds::Vector<int>();
    ASSERT_EQ(vector.capacity(), 2);
    vector.push_back(1);
    vector.push_back(2);
    vector.insert(1, -5);
    ASSERT_EQ(vector[0], 1);
    ASSERT_EQ(vector[1], -5);
    ASSERT_EQ(vector[2], 2);
    ASSERT_GT(vector.capacity(), 2);

}

/*
 * Check for attempts to unavailable memory.
 */
TEST(VectorFix, PushManyElementsToVectorAndRetrieveThemUsingIndexes)
{
    ghds::Vector<int> vector = ghds::Vector<int>();
    for (int i=0; i < 200; i++)
        vector.push_back(i+1);
    for (int i = 0; i < 200; i++)
        ASSERT_EQ(vector[i], i+1);
    ASSERT_GE(vector.capacity(), vector.size());
}

TEST(VectorFix, PushManyElementsToVectorAndInsertOneMoreInTheMiddle)
{
    ghds::Vector<int> vector = ghds::Vector<int>();
    for (int i=0; i < 20; i++)
        vector.push_back(i+1);
    vector.insert(10, 0);
    for (int i=0; i < vector.size(); i ++)
        std::cout << "Position: " << i << " >> " << vector[i] << std::endl;
    for (int i = 0; i < 10; i++)
        ASSERT_EQ(vector[i], i+1);
    ASSERT_EQ(vector[10], 0);
    for (int i = 11; i < vector.size(); i++)
        ASSERT_EQ(vector[i], i);
}



