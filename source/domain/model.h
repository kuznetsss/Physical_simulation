#ifndef DOMAIN_MODEL
#define DOMAIN_MODEL

#include <vector>

#include "utils/common_utils.h"
#include "utils/vector2f.h"
#include "common/ball_id.h"

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
    void removeBall(const common::BallId& ballId);

    void moveBall(const common::BallId& ballId, const utils::Vector2f& position);

    void setBallFixed(const common::BallId& ballId, bool fixed);
    void setBallFixed(const utils::Vector2f& position, bool fixed);

    common::BallId findBallByPosition(const utils::Vector2f& position) const;
    std::vector<utils::Vector2f> ballsPositions() const;

    void startSimulation();

    std::size_t ballsNumber() const;
    std::vector<common::BallId> ballIds() const;
    utils::Vector2f ballPosition(const common::BallId& ballId) const;

private:
    struct Impl;
    utils::ImplPtr<Impl> _d;
};

} // namespace domain

#endif // DOMAIN_MODEL
