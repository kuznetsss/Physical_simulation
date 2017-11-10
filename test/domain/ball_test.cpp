#include "domain/ball.h"

#include <gtest/gtest.h>
#include "test_extesions.h"

#include "utils/constants.h"

using namespace domain;

class Ball_Test: public ::testing::Test
{
protected:
    Ball ball;
    const utils::Vector2f initialPosition = utils::Vector2f(3.f, 5.f);
    const utils::Vector2f initialVelocity = utils::Vector2f(1.f, 2.f);

    void SetUp()
    {
        ball.setPosition(initialPosition);
        ball.setVelocity(initialVelocity);
    }
};

TEST_F(Ball_Test, RandomPosition)
{
    const Ball ball1;
    EXPECT_LE(ball1.position().x(), FIELD_LEFT_WALL);
    EXPECT_LE(ball1.position().y(), FIELD_UP_WALL);
    EXPECT_GE(ball1.position().x(), FIELD_RIGHT_WALL);
    EXPECT_GE(ball1.position().y(), FIELD_DOWN_WALL);

    const Ball ball2;
    EXPECT_VECTORS_NE(ball1.position(), ball2.position());
}

TEST_F(Ball_Test, ApplyForce)
{
    const utils::Vector2f force(5.f, 7.f);
    const float deltaT = 2.f;
    ball.applyForce(force, deltaT);
    EXPECT_VECTORS_EQ(ball.velocity(), utils::Vector2f(11.f, 16.f));
}

TEST_F(Ball_Test, MakeStep)
{
    const float deltaT = 2.f;
    ball.makeStep(deltaT);
    EXPECT_VECTORS_EQ(ball.position(), utils::Vector2f(5.f, 9.f));

    const auto latestPosition = ball.position();
    ball.setFixed(true);
    EXPECT_VECTORS_EQ(ball.position(), latestPosition);
}
