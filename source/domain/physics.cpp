#include "domain/physics.h"

#include "utils/vector2f.h"

namespace domain {

utils::Vector2f Physics::calculateForceForBall(const domain::BallPtr &ball,
                                               const std::unordered_map<std::size_t, domain::BallPtr> &idToBallMap)
{
    const auto ballPosition = ball->position();
    const auto ballId = ball->id().toStdSizeT();

    utils::Vector2f totalForce;
    for (const auto& idAndBall : idToBallMap) {
        if (idAndBall.first == ballId) continue;
        const auto deltaR = idAndBall.second->position() - ballPosition;
        totalForce += deltaR.normalized() * (deltaR.norm() - 1.f) / deltaR.normSquare();
    }
    return totalForce;
}

} // namespace domain
