#include "domain/model.h"

#include <unordered_map>
#include <thread>
#include <mutex>

#include "domain/ball.h"

namespace domain {

struct Model::Impl
{
    Impl();
    ~Impl();

    utils::Vector2f calculateForceForBall(const BallPtr& ball);
    void simulate();

    std::unordered_map<std::size_t, BallPtr> _idToBallMap;
    std::mutex _mutex;
    bool _simulationIsActive = false;
    std::unique_ptr<std::thread> _thread;
    static constexpr float _deltaT = 1.f;
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

void Model::removeBall(const BallId& ballId)
{
    std::lock_guard<std::mutex> lock(_d->_mutex);
    _d->_idToBallMap.erase(_d->_idToBallMap.find(ballId.toStdSizeT()));
}

void Model::removeBall(const utils::Vector2f &position)
{
    const auto ballId = findBallByPosition(position);
    if (ballId.toStdSizeT() != BallId::NULLID) removeBall(ballId);
}

void Model::moveBall(const BallId& ballId, const utils::Vector2f& position)
{
    std::lock_guard<std::mutex> lock(_d->_mutex);
    _d->_idToBallMap.at(ballId.toStdSizeT())->setPosition(position);
}

BallId Model::findBallByPosition(const utils::Vector2f& position) const
{
    for (const auto& idAndBall : _d->_idToBallMap) {
        if (idAndBall.second->position() == position)
            return idAndBall.first;
    }
    return BallId::NULLID;
}

void Model::startSimulation()
{
    _d->_simulationIsActive = true;
    _d->_thread = std::make_unique<std::thread>(&Impl::simulate, std::ref(*_d.get()));
}

Model::Impl::Impl()
{
   const std::size_t ballsInitialNumber = std::rand() % 10;
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

utils::Vector2f Model::Impl::calculateForceForBall(const BallPtr& ball)
{
    const auto ballPosition = ball->position();
    const auto ballId = ball->id().toStdSizeT();

    utils::Vector2f totalForce;
    for (auto& idAndBall : _idToBallMap) {
        if (idAndBall.first == ballId) continue;
        const auto deltaR = ballPosition - idAndBall.second->position();
        totalForce += deltaR.normalized() * (deltaR.norm() - 1.f) / deltaR.normSquare();
    }
    return totalForce;
}

void Model::Impl::simulate()
{
    for (auto& idAndBall : _idToBallMap) {
        const auto force = calculateForceForBall(idAndBall.second);
        idAndBall.second->applyForce(force, Impl::_deltaT);
    }

    for (auto& idAndBall : _idToBallMap) {
        idAndBall.second->makeStep(Impl::_deltaT);
    }
}

} // namespace domain
