#include "domain/model.h"

#include <gtest/gtest.h>
#include <math.h>
#include <stdlib.h>
#include <thread>

#include "test_extesions.h"
#include "utils/id.h"

#include "common/field_sizes.h"
#include "domain/ball.h"

using namespace domain;

class Model_Test : public ::testing::Test {
 protected:
  Model model;
  void SetUp() { model.setDeltaT(0.01f); }
  void clearModel() {
    for (const auto& ballId : model.ballIds()) {
      model.removeBall(ballId);
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }
};

TEST_F(Model_Test, BallOperations) {
  clearModel();
  const auto ballPosition = utils::Vector2f(25.f, 35.f);
  model.addBall(ballPosition);
  std::this_thread::sleep_for(std::chrono::milliseconds(10));
  EXPECT_EQ(model.ballsNumber(), 1);
  EXPECT_FALSE(model.findBallByPosition(ballPosition).isNull());

  const auto newBallPosition = utils::Vector2f(100.f, 500.f);
  model.moveBall(model.ballIds().at(0), newBallPosition);
  model.removeBall(ballPosition);
  std::this_thread::sleep_for(std::chrono::milliseconds(100));
  EXPECT_EQ(model.ballsNumber(), 1);
  model.removeBall(newBallPosition);
  std::this_thread::sleep_for(std::chrono::milliseconds(100));
  EXPECT_EQ(model.ballsNumber(), 0);
}

TEST_F(Model_Test, AddingRemovingManyBalls) {
  clearModel();
  model.startStopSimulation();
  constexpr int BALLS_NUM = 1000;
  for (int i = 0; i < BALLS_NUM; ++i) model.addBall(utils::Vector2f(i, i));
  std::this_thread::sleep_for(std::chrono::milliseconds(100));
  EXPECT_EQ(model.ballsNumber(), BALLS_NUM);
  const auto ids = model.ballIds();
  for (const auto& id : ids) model.removeBallLater(id);
  std::this_thread::sleep_for(std::chrono::milliseconds(100));
  EXPECT_EQ(model.ballsNumber(), 0);
}

TEST_F(Model_Test, SimulationRunning) {
  const auto initialBallsNumber = model.ballsNumber();
  model.startStopSimulation();

  EXPECT_NO_THROW(model.addBall(utils::Vector2f()));
  std::this_thread::sleep_for(std::chrono::milliseconds(100));
  EXPECT_EQ(model.ballsNumber(), initialBallsNumber + 1);

  EXPECT_NO_THROW(model.removeBall(utils::Vector2f()));

  const auto ballId = model.ballIds().at(0);
  model.setBallFixed(ballId, true);
  const auto newBallPosition = utils::Vector2f(100.f, 300.f);
  model.moveBall(ballId, newBallPosition);
  EXPECT_VECTORS_EQ(model.ballPosition(ballId), newBallPosition);
  EXPECT_NO_THROW(model.removeBall(ballId));
}

TEST_F(Model_Test, BallsMoving) {
  clearModel();
  const std::vector<utils::Vector2f> ballsPositions = {
      utils::Vector2f(100.f, 100.f), utils::Vector2f(101.f, 100.f),
      utils::Vector2f(100.5f, 100.f + std::sqrt(0.75f))};
  std::vector<utils::Id> ballIds;
  for (const auto& position : ballsPositions) {
    ballIds.emplace_back(model.addBall(position));
  }
  model.startStopSimulation();
  sleep(1);

  for (std::size_t i = 0; i < ballIds.size(); i++) {
    EXPECT_VECTORS_EQ(model.ballPosition(ballIds[i]), ballsPositions[i]);
  }

  model.addBall(utils::Vector2f(101.f, 101.f));
  std::this_thread::sleep_for(std::chrono::seconds(1));

  for (std::size_t i = 0; i < ballIds.size(); i++) {
    EXPECT_VECTORS_NE(model.ballPosition(ballIds[i]), ballsPositions[i]);
  }
}

TEST_F(Model_Test, LongSimulation) {
  model.setDeltaT(10.f);
  model.startStopSimulation();
  std::this_thread::sleep_for(std::chrono::seconds(10));
  for (const auto& ballPosition : model.ballsPositions()) {
    EXPECT_TRUE(ballPosition.x() > Ball::RADIUS &&
                ballPosition.x() < FIELD_WIDTH - Ball::RADIUS);
    EXPECT_TRUE(ballPosition.y() > Ball::RADIUS &&
                ballPosition.y() < FIELD_HEIGHT - Ball::RADIUS);
  }
}
