#ifndef DOMAIN_PHYSICS
#define DOMAIN_PHYSICS

#include <unordered_map>

#include "domain/ball.h"

namespace domain {

class Physics {
public:
    static utils::Vector2f calculateForceForBall(const BallPtr& ball,
                                                 const std::unordered_map<std::size_t, BallPtr>& idToBallMap);
};

} // namespace domain
#endif // DOMAIN_PHYSICS
