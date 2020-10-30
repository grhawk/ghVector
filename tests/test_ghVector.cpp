#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err58-cpp"
#include<gtest/gtest.h>

#include<ghVector.cpp>
#include "testObjects.h"

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

TEST(VectorFix, PushOneElementAndInsertOneBefore)
{
    ghds::Vector<int> vector = ghds::Vector<int>();
    ASSERT_EQ(vector.capacity(), 2);
    vector.push_back(2);
    vector.insert(0, -5);
    ASSERT_EQ(vector[0], -5);
    ASSERT_EQ(vector[1], 2);
    ASSERT_EQ(vector.capacity(), vector.size());
    ASSERT_EQ(vector.capacity(), 2);

}

TEST(VectorFix, PushOneElementAndInsertOneAfter)
{
    ghds::Vector<int> vector = ghds::Vector<int>();
    ASSERT_EQ(vector.capacity(), 2);
    vector.push_back(2);
    ASSERT_ANY_THROW(vector.insert(1, -5));
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

TEST(VectorFix, PushTwoElementsAndInsertOneBeforeCheckCapacityIncreases)
{
    ghds::Vector<int> vector = ghds::Vector<int>();
    ASSERT_EQ(vector.capacity(), 2);
    vector.push_back(1);
    vector.push_back(2);
    vector.insert(0, -5);
    ASSERT_EQ(vector[1], 1);
    ASSERT_EQ(vector[0], -5);
    ASSERT_EQ(vector[2], 2);
    ASSERT_EQ(vector.size(), 3);
    ASSERT_GT(vector.capacity(), 2);
}

TEST(VectorFix, PushTwoElementsAndInsertOneAfterCheckCapacityIncreases)
{
    ghds::Vector<int> vector = ghds::Vector<int>();
    ASSERT_EQ(vector.capacity(), 2);
    vector.push_back(1);
    vector.push_back(2);
    ASSERT_ANY_THROW(vector.insert(3, -5));
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
    for (int i=0; i < 200; i++)
        vector.push_back(i+1);
    vector.insert(10, 0);
    vector.insert(10, 0);
    vector.insert(10, 0);
    vector.insert(10, 0);
    vector.insert(10, 0);
    for (int i = 0; i < 10; i++)
        ASSERT_EQ(vector[i], i+1);
    ASSERT_EQ(vector[10], 0);
    for (int i = 15; i < vector.size(); i++)
        ASSERT_EQ(vector[i], (i - 4));
    ASSERT_EQ(vector.size(), 205);
}

/*
 * Testing number of copy needed
 */
TEST(VectorOfVectors, GenerateAVectorOfVectors)
{
    initializeMonitoringMap();
    SimpleVector3 v31 = SimpleVector3(1.0, 1.0, 1.0);
    SimpleVector3 v32 = v31;
    SimpleVector3 v33 = std::move(v31);
    v33.printMonitoringMap();
    ASSERT_EQ(v33.getCalls()["calls to copy"], 1);
    ASSERT_EQ(v33.getCalls()["calls to floats"], 1);
    ASSERT_EQ(v33.getCalls()["calls to move"], 1);
    ASSERT_EQ(v33.getCalls()["calls to default"], 0);
}

#pragma clang diagnostic pop