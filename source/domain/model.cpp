#include "domain/model.h"

#include <unordered_map>
#include <thread>
#include <mutex>

#include "domain/ball.h"
#include "domain/physics.h"

namespace domain {

struct Model::Impl
{
    Impl();
    ~Impl();

    void simulate();

    std::unordered_map<std::size_t, BallPtr> _idToBallMap;
    mutable std::mutex _mutex;
    bool _simulationIsActive = false;
    std::unique_ptr<std::thread> _thread;
    static constexpr float _deltaT = 0.001f;
};

Model::Model():
    _d(std::make_unique<Impl>())
{}

Model::~Model() = default;

void Model::addBall(const utils::Vector2f &position)
{
    std::lock_guard<std::mutex> lock(_d->_mutex);
    const auto newBall = std::make_shared<Ball>(position);
    _d->_idToBallMap.emplace(newBall->id().toStdSizeT(), newBall);
}

void Model::removeBall(const common::BallId& ballId)
{
    std::lock_guard<std::mutex> lock(_d->_mutex);
    _d->_idToBallMap.erase(_d->_idToBallMap.find(ballId.toStdSizeT()));
}

void Model::removeBall(const utils::Vector2f &position)
{
    const auto ballId = findBallByPosition(position);
    if (!ballId.isNull()) removeBall(ballId);
}

void Model::moveBall(const common::BallId& ballId, const utils::Vector2f& position)
{
    std::lock_guard<std::mutex> lock(_d->_mutex);
    _d->_idToBallMap.at(ballId.toStdSizeT())->setPosition(position);
}

void Model::setBallFixed(const common::BallId& ballId, const bool fixed)
{
    std::lock_guard<std::mutex> lock(_d->_mutex);
    _d->_idToBallMap.at(ballId.toStdSizeT())->setFixed(fixed);
}

void Model::setBallFixed(const utils::Vector2f& position, const bool fixed)
{
    setBallFixed(findBallByPosition(position), fixed);
}

common::BallId Model::findBallByPosition(const utils::Vector2f& position) const
{
    std::lock_guard<std::mutex> lock(_d->_mutex);
    for (const auto& idAndBall : _d->_idToBallMap) {
        if (idAndBall.second->position() == position)
            return idAndBall.first;
    }
    return common::BallId::NULLID;
}

std::vector<utils::Vector2f> Model::ballsPositions() const
{
    std::lock_guard<std::mutex> lock(_d->_mutex);
    std::vector<utils::Vector2f> result;
    for (const auto& idAndBall : _d->_idToBallMap) {
        result.emplace_back(idAndBall.second->position());
    }
    return result;
}

void Model::startSimulation()
{
    _d->_simulationIsActive = true;
    _d->_thread = std::make_unique<std::thread>(&Impl::simulate, std::ref(*_d.get()));
}

std::size_t Model::ballsNumber() const
{
    std::lock_guard<std::mutex> lock(_d->_mutex);
    return _d->_idToBallMap.size();
}

std::vector<common::BallId> Model::ballIds() const
{
    std::lock_guard<std::mutex> lock(_d->_mutex);
    std::vector<common::BallId> result;
    for (const auto& idAndBall : _d->_idToBallMap) {
        result.push_back(idAndBall.first);
    }
    return result;
}

utils::Vector2f Model::ballPosition(const common::BallId& ballId) const
{
    std::lock_guard<std::mutex> lock(_d->_mutex);
    return _d->_idToBallMap.at(ballId.toStdSizeT())->position();
}

Model::Impl::Impl()
{
    // TODO вынести в константу максимальное число шаров при старте
   const std::size_t ballsInitialNumber = 10;
   for (std::size_t i = 0; i < ballsInitialNumber; i++) {
       // TODO дублирование с addBall
       const auto newBall = std::make_shared<Ball>();
       _idToBallMap.emplace(newBall->id().toStdSizeT(), newBall);
   }
}

Model::Impl::~Impl()
{
    if (_simulationIsActive) {
        _mutex.lock();
        _simulationIsActive = false;
        _mutex.unlock();
        _thread->join();
    }
}

void Model::Impl::simulate()
{
    while (_simulationIsActive) {
        std::lock_guard<std::mutex> lock(_mutex);
        for (auto& idAndBall : _idToBallMap) {
            const auto force = Physics::calculateForceForBall(idAndBall.second, _idToBallMap);
            idAndBall.second->applyForce(force, Impl::_deltaT);
        }

        for (auto& idAndBall : _idToBallMap) {
            idAndBall.second->makeStep(Impl::_deltaT);
        }
    }
}

} // namespace domain
