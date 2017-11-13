#include "domain/ball.h"

#include <gtest/gtest.h>
#include "test_extesions.h"

#include "utils/vector2f.h"
#include "utils/id.h"
#include "common/field_sizes.h"

using namespace domain;

class Ball_Test: public ::testing::Test
{
protected:
    Ball ball;
    const utils::Vector2f initialPosition = utils::Vector2f(300.f, 500.f);
    const utils::Vector2f initialSpeed = utils::Vector2f(1.f, 2.f);

    void SetUp()
    {
        ball.setPosition(initialPosition);
        ball.setSpeed(initialSpeed);
    }
};

TEST_F(Ball_Test, RandomPositionAndId)
{
    const Ball ball1;
    EXPECT_LE(ball1.position().x(), FIELD_WIDTH - Ball::RADIUS);
    EXPECT_LE(ball1.position().y(), FIELD_HEIGHT - Ball::RADIUS);
    EXPECT_GE(ball1.position().x(), float(Ball::RADIUS));
    EXPECT_GE(ball1.position().y(), float(Ball::RADIUS));

    const Ball ball2;
    EXPECT_NE(ball1.id(), ball2.id());
}

TEST_F(Ball_Test, ApplyForce)
{
    const utils::Vector2f force(5.f, 7.f);
    const float deltaT = 2.f;
    ball.applyForce(force, deltaT);
    EXPECT_VECTORS_EQ(ball.speed(), utils::Vector2f(11.f, 16.f));
}

TEST_F(Ball_Test, MakeStep)
{
    const float deltaT = 2.f;
    ball.makeStep(deltaT);
    EXPECT_VECTORS_EQ(ball.position(), utils::Vector2f(302.f, 504.f));

    const auto latestPosition = ball.position();
    ball.setFixed(true);
    EXPECT_VECTORS_EQ(ball.position(), latestPosition);
    ball.setFixed(false);

    const auto rightUpCorner = utils::Vector2f(FIELD_WIDTH - Ball::RADIUS - 0.5f, FIELD_HEIGHT - Ball::RADIUS - 0.5f);
    ball.setPosition(rightUpCorner);
    ball.makeStep(deltaT);

    EXPECT_VECTORS_EQ(ball.speed(), initialSpeed * (-1.f));
    EXPECT_VECTORS_EQ(ball.position(), rightUpCorner - initialSpeed * deltaT);

}
