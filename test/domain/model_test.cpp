#include "domain/model.h"

#include <gtest/gtest.h>
#include <math.h>
#include <stdlib.h>

#include "test_extesions.h"
#include "domain/ball_id.h"

using namespace domain;

class Model_Test: public ::testing::Test
{
protected:
   Model model;
   void clearModel() {
        for (const auto ballId : model.ballIds()) {
            model.removeBall(ballId);
        }
   }
};

TEST_F(Model_Test, BallOperations)
{
    clearModel();
    const auto ballPosition = utils::Vector2f(0.f, 0.f);
    model.addBall(ballPosition);
    EXPECT_EQ(model.ballsNumber(), 1);
    EXPECT_NE(model.findBallByPosition(ballPosition), BallId(BallId::NULLID));
    const auto newBallPosition = utils::Vector2f(10.f, -50.f);
    model.moveBall(model.ballIds().at(0), newBallPosition);
    model.removeBall(ballPosition);
    EXPECT_EQ(model.ballsNumber(), 1);
    model.removeBall(newBallPosition);
    EXPECT_EQ(model.ballsNumber(), 0);
}

TEST_F(Model_Test, SimulationRunning)
{
    const auto initialBallsNumber = model.ballsNumber();
    model.startSimulation();

    EXPECT_NO_THROW(model.addBall(utils::Vector2f()));
    EXPECT_EQ(model.ballsNumber(), initialBallsNumber + 1);

    EXPECT_NO_THROW(model.removeBall(utils::Vector2f()));

    const auto ballId = model.ballIds().at(0);
    model.setBallFixed(ballId, true);
    const auto newBallPosition = utils::Vector2f(1.f, 3.f);
    model.moveBall(ballId, newBallPosition);
    EXPECT_VECTORS_EQ(model.ballPosition(ballId), newBallPosition);
    EXPECT_NO_THROW(model.removeBall(ballId));
}

TEST_F(Model_Test, BallsMoving)
{
    clearModel();
    const std::vector<utils::Vector2f> ballsPositions = {utils::Vector2f(), utils::Vector2f(1.f, 0.f),
                                                         utils::Vector2f(0.5f, std::sqrt(0.75f))};
    for (const auto& position : ballsPositions) {
        model.addBall(position);
    }
    model.startSimulation();
    sleep(1);

    for (const auto& position : ballsPositions) {
        EXPECT_NE(model.findBallByPosition(position), BallId(BallId::NULLID));
    }

    model.addBall(utils::Vector2f(0.5f, 0.f));
    sleep(1);

    for (const auto& position : ballsPositions) {
        EXPECT_EQ(model.findBallByPosition(position), BallId(BallId::NULLID));
    }
}
