#ifndef DOMAIN_MODEL
#define DOMAIN_MODEL

#include <vector>

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

    void setBallFixed(const BallId& ballId, bool fixed);
    void setBallFixed(const utils::Vector2f& position, bool fixed);

    BallId findBallByPosition(const utils::Vector2f& position) const;

    void startSimulation();

    std::size_t ballsNumber() const;
    std::vector<BallId> ballIds() const;
    utils::Vector2f ballPosition(const BallId& ballId) const;

private:
    struct Impl;
    utils::ImplPtr<Impl> _d;
};

} // namespace domain

#endif // DOMAIN_MODEL
