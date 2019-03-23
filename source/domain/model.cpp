#include "domain/model.h"

#include <mutex>
#include <thread>
#include <unordered_map>

#include "domain/ball.h"
#include "domain/physics.h"

namespace domain {

struct Model::Impl {
  Impl();
  ~Impl();

  void simulate();
  void stopSimulation();

  std::unordered_map<std::size_t, BallPtr> _idToBallMap;
  mutable std::mutex _idToBallMapMutex;
  mutable std::mutex _mutex;
  bool _simulationIsActive = false;
  std::unique_ptr<std::thread> _thread;
  float _deltaT = 0.001f;
};

Model::Model() : _d(std::make_unique<Impl>()) {}

Model::~Model() = default;

utils::Id Model::addBall(const utils::Vector2f& position) {
  std::lock_guard<std::mutex> lock(_d->_idToBallMapMutex);
  const auto newBall = std::make_shared<Ball>(position);
  _d->_idToBallMap.emplace(newBall->id().toStdSizeT(), newBall);
  return newBall->id();
}

void Model::removeBall(const utils::Id& ballId) {
  std::lock_guard<std::mutex> lock(_d->_idToBallMapMutex);
  _d->_idToBallMap.erase(_d->_idToBallMap.find(ballId.toStdSizeT()));
}

void Model::removeBall(const utils::Vector2f& position) {
  const auto ballId = findBallByPosition(position);
  if (!ballId.isNull()) removeBall(ballId);
}

void Model::moveBall(const utils::Id& ballId, const utils::Vector2f& position) {
  std::lock_guard<std::mutex> lock(_d->_mutex);
  _d->_idToBallMap.at(ballId.toStdSizeT())->setPosition(position);
}

void Model::setBallFixed(const utils::Id& ballId, const bool fixed) {
  std::lock_guard<std::mutex> lock(_d->_mutex);
  if (!fixed)
    _d->_idToBallMap.at(ballId.toStdSizeT())->setSpeed(utils::Vector2f());
  _d->_idToBallMap.at(ballId.toStdSizeT())->setFixed(fixed);
}

utils::Id Model::findBallByPosition(const utils::Vector2f& position) const {
  std::lock_guard<std::mutex> lock(_d->_mutex);
  for (const auto& idAndBall : _d->_idToBallMap) {
    if ((idAndBall.second->position() - position).normSquare() <
        Ball::RADIUS_SQUARE)
      return idAndBall.first;
  }
  return utils::Id::NULLID;
}

std::vector<utils::Vector2f> Model::ballsPositions() const {
  std::lock_guard<std::mutex> lock(_d->_mutex);
  std::vector<utils::Vector2f> result;
  for (const auto& idAndBall : _d->_idToBallMap) {
    result.emplace_back(idAndBall.second->position());
  }
  return result;
}

void Model::startStopSimulation() {
  if (!_d->_simulationIsActive) {
    _d->_simulationIsActive = true;
    _d->_thread =
        std::make_unique<std::thread>(&Impl::simulate, std::ref(*_d.get()));
  } else {
    _d->_simulationIsActive = false;
    for (auto& idAndBall : _d->_idToBallMap)
      idAndBall.second->setSpeed(utils::Vector2f());
    _d->stopSimulation();
  }
}

float Model::deltaT() const { return _d->_deltaT; }

void Model::setDeltaT(float deltaT) {
  std::lock_guard<std::mutex> lock(_d->_mutex);
  _d->_deltaT = deltaT;
}

std::size_t Model::ballsNumber() const {
  std::lock_guard<std::mutex> lock(_d->_mutex);
  return _d->_idToBallMap.size();
}

std::vector<utils::Id> Model::ballIds() const {
  std::lock_guard<std::mutex> lock(_d->_mutex);
  std::vector<utils::Id> result;
  for (const auto& idAndBall : _d->_idToBallMap) {
    result.push_back(idAndBall.first);
  }
  return result;
}

utils::Vector2f Model::ballPosition(const utils::Id& ballId) const {
  std::lock_guard<std::mutex> lock(_d->_mutex);
  return _d->_idToBallMap.at(ballId.toStdSizeT())->position();
}

Model::Impl::Impl() {
  const std::size_t ballsInitialNumber = 2;
  for (std::size_t i = 0; i < ballsInitialNumber; i++) {
    const auto newBall = std::make_shared<Ball>();
    _idToBallMap.emplace(newBall->id().toStdSizeT(), newBall);
  }
}

Model::Impl::~Impl() {
  if (_simulationIsActive) stopSimulation();
}

void Model::Impl::simulate() {
  while (_simulationIsActive) {
    {
      std::lock_guard<std::mutex> lock_map(_idToBallMapMutex);
      for (auto& idAndBall : _idToBallMap) {
        std::lock_guard<std::mutex> lock(_mutex);
        const auto force =
            Physics::calculateForceForBall(idAndBall.second, _idToBallMap);
        idAndBall.second->applyForce(force, Impl::_deltaT);
      }
    }

    {
      std::lock_guard<std::mutex> lock_map(_idToBallMapMutex);
      for (auto& idAndBall : _idToBallMap) {
        std::lock_guard<std::mutex> lock(_mutex);
        idAndBall.second->makeStep(Impl::_deltaT);
      }
    }
  }
}

void Model::Impl::stopSimulation() {
  _mutex.lock();
  _simulationIsActive = false;
  _mutex.unlock();
  _thread->join();
}

}  // namespace domain
