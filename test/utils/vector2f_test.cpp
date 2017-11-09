#include "utils/vector2f.h"

#include <gtest/gtest.h>
#include <iostream>

#define EXPECT_VECTORS_EQ(vec1, vec2)		    \
    EXPECT_FLOAT_EQ((vec1).x(), (vec2).x()); 	\
    EXPECT_FLOAT_EQ((vec1).y(), (vec2).y());

using namespace utils;

class Vector2f_test: public ::testing::Test
{
protected:
    const Vector2f vec1 = Vector2f(3.f, 4.f);
    const Vector2f vec2 = Vector2f(7.f, 8.f);
};

TEST_F(Vector2f_test, Norm)
{
    EXPECT_FLOAT_EQ(vec1.normSquare(), 25.f);
    EXPECT_FLOAT_EQ(vec1.norm(), 5.f);
}

TEST_F(Vector2f_test, Arithmetic)
{
    EXPECT_VECTORS_EQ(vec1 + vec2, Vector2f(10.f, 12.f));
    EXPECT_VECTORS_EQ(vec1 - vec2, Vector2f(-4.f, -4.f));
    EXPECT_VECTORS_EQ(vec1 * 0.5f, Vector2f(1.5f, 2.f));
    EXPECT_VECTORS_EQ(vec1 / 4.f, Vector2f(0.75f, 1.f));

    Vector2f testVec = vec1;
    testVec += vec2;
    EXPECT_VECTORS_EQ(testVec, vec1 + vec2);
    testVec -= vec2;
    EXPECT_VECTORS_EQ(testVec, vec1);
}
