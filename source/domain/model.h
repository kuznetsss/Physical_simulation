#ifndef DOMAIN_MODEL
#define DOMAIN_MODEL

#include <vector>

#include "utils/common_utils.h"
#include "utils/vector2f.h"
#include "utils/id.h"

namespace utils {

class Vector2f;

} //namespace utils

namespace domain {

class Model: public utils::NonCopyable
{
public:
    Model();
    ~Model();

    utils::Id addBall(const utils::Vector2f& position);
    void removeBall(const utils::Vector2f& position);
    void removeBall(const utils::Id& ballId);

    void moveBall(const utils::Id& ballId, const utils::Vector2f& position);

    void setBallFixed(const utils::Id& ballId, bool fixed);

    utils::Id findBallByPosition(const utils::Vector2f& position) const;
    std::vector<utils::Vector2f> ballsPositions() const;

    void startStopSimulation();

    void setDeltaT(float deltaT);

    std::size_t ballsNumber() const;
    std::vector<utils::Id> ballIds() const;
    utils::Vector2f ballPosition(const utils::Id& ballId) const;

private:
    struct Impl;
    utils::ImplPtr<Impl> _d;
};

} // namespace domain

#endif // DOMAIN_MODEL
