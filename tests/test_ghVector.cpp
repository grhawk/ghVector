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

TEST(VectorFix, RemoveEmptyMemory){
    ghds::Vector<int> vector = ghds::Vector<int>();
    vector.push_back(1);
    vector.push_back(2);
    vector.push_back(3);
    vector.push_back(4);
    vector.push_back(5);
    ASSERT_EQ(vector.capacity(), 6);
    ASSERT_EQ(vector.size(), 5);
    vector.shrink_to_fit();
    ASSERT_EQ(vector.capacity(), 5);
    ASSERT_EQ(vector.size(), 5);
}

TEST(VectorFix, ClearVector){
    ghds::Vector<int> vector = ghds::Vector<int>();
    vector.push_back(1);
    vector.push_back(2);
    vector.push_back(3);
    vector.push_back(4);
    vector.push_back(5);
    ASSERT_EQ(vector.capacity(), 6);
    ASSERT_EQ(vector.size(), 5);
    vector.Clear();
    ASSERT_EQ(vector.capacity(), 6);
    ASSERT_EQ(vector.size(), 0);
}

TEST(VectorFix, PopBack){
    ghds::Vector<int> vector = ghds::Vector<int>();
    vector.push_back(1);
    vector.push_back(2);
    vector.push_back(3);
    vector.push_back(4);
    vector.push_back(5);
    ASSERT_EQ(vector.capacity(), 6);
    ASSERT_EQ(vector.size(), 5);
    vector.pop_back();
    ASSERT_EQ(vector.capacity(), 6);
    ASSERT_EQ(vector.size(), 4);
    ASSERT_EQ(vector[vector.size() - 1], 4);
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
TEST(VectorOfVectors, TestVectorInVector)
{
    SimpleVector3::initializeMonitoringMap();
    SimpleVector3 v31 = SimpleVector3(1.0, 1.0, 1.0); // floats constructor
    SimpleVector3 v32 = v31; // copy constructor
    v32.x(2.0);
    ASSERT_EQ(v32.x(), 2.0);
    ASSERT_EQ(v31.x(), 1.0);
    SimpleVector3 v33 = std::move(v31); // move constructor
    SimpleVector3 v34; // default constructor
    v34 = v32; // copy operator
    v34 = std::move(v32); // move operator
    SimpleVector3::printMonitoringMap();
    ASSERT_EQ(SimpleVector3::calls_list()["calls to copy operator"], 1);
    ASSERT_EQ(SimpleVector3::calls_list()["calls to move operator"], 1);
    ASSERT_EQ(SimpleVector3::calls_list()["calls to copy constructor"], 1);
    ASSERT_EQ(SimpleVector3::calls_list()["calls to floats constructor"], 1);
    ASSERT_EQ(SimpleVector3::calls_list()["calls to move constructor"], 1);
    ASSERT_EQ(SimpleVector3::calls_list()["calls to default constructor"], 1);
}

TEST(VectorOfVectors, GenerateAVectorOfVectorsWithoutReallocation)
{
    SimpleVector3::initializeMonitoringMap();
    ghds::Vector<SimpleVector3> v = ghds::Vector<SimpleVector3>();
    v.push_back(SimpleVector3(1.0, 1.0, 2.0));
    v.push_back(SimpleVector3(2.0, 1.0, 2.0));
    SimpleVector3::printMonitoringMap();
    ASSERT_EQ(v[0].x(), 1.0);
    ASSERT_EQ(v[1].x(), 2.0);
    ASSERT_EQ(SimpleVector3::calls_list()["calls to copy constructor"], 0);
    ASSERT_EQ(SimpleVector3::calls_list()["calls to floats constructor"], 2);
    ASSERT_EQ(SimpleVector3::calls_list()["calls to move constructor"], 0);
    ASSERT_EQ(SimpleVector3::calls_list()["calls to default constructor"], 0);
    ASSERT_EQ(SimpleVector3::calls_list()["calls to move operator"], 2);
}

TEST(VectorOfVectors, GenerateAVectorOfVectorsWithReallocation)
{
    SimpleVector3::initializeMonitoringMap();
    ghds::Vector<SimpleVector3> v = ghds::Vector<SimpleVector3>();
    v.push_back(SimpleVector3(1, 1, 2));
    v.push_back(SimpleVector3(2, 1, 2));
    v.push_back(SimpleVector3(3, 1, 2));
    v[0].print();
    v[1].print();
    v[2].print();
    SimpleVector3::printMonitoringMap();
    ASSERT_EQ(v[0].x(), 1.0);
    ASSERT_EQ(v[1].x(), 2.0);
    ASSERT_EQ(v[2].x(), 3.0);
    ASSERT_EQ(SimpleVector3::calls_list()["calls to copy constructor"], 0);
    ASSERT_EQ(SimpleVector3::calls_list()["calls to floats constructor"], 3);
    ASSERT_EQ(SimpleVector3::calls_list()["calls to move constructor"], 0);
    ASSERT_EQ(SimpleVector3::calls_list()["calls to copy operator"], 0);
    ASSERT_EQ(SimpleVector3::calls_list()["calls to move operator"], 5);
}

TEST(VectorOfVectors, GenerateAVectorOfVectorsWithReallocationAndMixtRAndLValue)
{
    SimpleVector3::initializeMonitoringMap();
    ghds::Vector<SimpleVector3> v = ghds::Vector<SimpleVector3>();
//    std::vector<SimpleVector3> v = std::vector<SimpleVector3>();
    SimpleVector3 v3a = SimpleVector3(100, 0, 2);
    SimpleVector3 v3b = SimpleVector3(200, 0, 2);
    v.push_back(SimpleVector3(1, 1, 2));
    v.push_back(SimpleVector3(2, 1, 2));
    v.push_back(SimpleVector3(3, 1, 2));
    v.push_back(v3a);
    v.push_back(std::move(v3b));
    v[0].print();
    v[1].print();
    v[2].print();
    v[3].print();
    v[4].print();
    SimpleVector3::printMonitoringMap();
    ASSERT_EQ(v[0].x(), 1);
    ASSERT_EQ(v[1].x(), 2);
    ASSERT_EQ(v[2].x(), 3);
    ASSERT_EQ(v[3].x(), 100);
    ASSERT_EQ(v3a.x(), 100);
    ASSERT_EQ(SimpleVector3::calls_list()["calls to default constructor"], 0);
    ASSERT_EQ(SimpleVector3::calls_list()["calls to copy constructor"], 1);
    ASSERT_EQ(SimpleVector3::calls_list()["calls to floats constructor"], 5);
    ASSERT_EQ(SimpleVector3::calls_list()["calls to move constructor"], 0);
    ASSERT_EQ(SimpleVector3::calls_list()["calls to copy operator"], 0);
    ASSERT_EQ(SimpleVector3::calls_list()["calls to move operator"], 14);
}

TEST(VectorOfVectors, TestClearFunction){
    SimpleVector3::initializeMonitoringMap();
    ghds::Vector<SimpleVector3> v = ghds::Vector<SimpleVector3>();
    for (size_t i = 0; i < 20; i++) {
        v.push_back(SimpleVector3(i, 0, 2));
    }
    ASSERT_EQ(v.capacity(), 28);
    ASSERT_EQ(v.size(), 20);
    std::cout << " >>>> CLEAR!" << std::endl;
    v.Clear();
    std::cout << " >>>> CLEAR DONE!" << std::endl;
    ASSERT_EQ(v.capacity(), 28);
    ASSERT_EQ(v.size(), 0);
    SimpleVector3::printMonitoringMap();
}

TEST(VectorOfVectors, TestClearFunctionThenPushBackAgain){
    SimpleVector3::initializeMonitoringMap();
    ghds::Vector<SimpleVector3> v = ghds::Vector<SimpleVector3>();
    for (size_t i = 0; i < 20; i++) {
        v.push_back(SimpleVector3(i, 0, 2));
    }
    ASSERT_EQ(v.capacity(), 28);
    ASSERT_EQ(v.size(), 20);
    std::cout << " >>>> CLEAR!" << std::endl;
    v.Clear();
    std::cout << " >>>> CLEAR DONE!" << std::endl;
    ASSERT_EQ(v.capacity(), 28);
    ASSERT_EQ(v.size(), 0);
    for (size_t i = 0; i < 10; i++) {
        v.push_back(SimpleVector3(i, 0, 2));
    }
    ASSERT_EQ(v.capacity(), 28);
    ASSERT_EQ(v.size(), 10);
    SimpleVector3::printMonitoringMap();
}

TEST(VectorOfVectors, TestPopBackFunctionThenPushBackAgain) {
    SimpleVector3::initializeMonitoringMap();
    ghds::Vector<SimpleVector3> v = ghds::Vector<SimpleVector3>();
    for (size_t i = 0; i < 20; i++) {
        v.push_back(SimpleVector3(i, 0, 2));
    }
    ASSERT_EQ(v.capacity(), 28);
    ASSERT_EQ(v.size(), 20);
    v.pop_back();
    ASSERT_EQ(v.capacity(), 28);
    ASSERT_EQ(v.size(), 19);
    for (size_t i = 0; i < 20; i++) {
        v.push_back(SimpleVector3(i, 0, 2));
    }
    ASSERT_EQ(v.capacity(), 42);
    ASSERT_EQ(v.size(), 39);
}


#pragma clang diagnostic pop