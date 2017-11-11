#ifndef DOMAIN_MODEL
#define DOMAIN_MODEL

#include "utils/common_utils.h"
#include "utils/vector2f.h"
#include "domain/ball_id.h"

namespace utils {

class Vector2f;

} //namespace utils

namespace domain {

class Model: public utils::NonCopyable
{
public:
    Model();
    ~Model();

    void addBall(const utils::Vector2f& position);
    void removeBall(const utils::Vector2f& position);
    void removeBall(const BallId& ballId);

    void moveBall(const BallId& ballId, const utils::Vector2f& position);

    BallId findBallByPosition(const utils::Vector2f& position) const;

    void startSimulation();

private:
    struct Impl;
    utils::ImplPtr<Impl> _d;
};

} // namespace domain

#endif // DOMAIN_MODEL
