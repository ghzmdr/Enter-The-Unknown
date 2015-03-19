#ifndef RUNNING_ENTITY
#define RUNNING_ENTITY

#include "Entities/Entity.hpp"

class RunningEntity : public Entity
{

public:
    static constexpr float runFactor {1.5};

    virtual void update();

    RunningEntity();
    float getSpeed();

    void checkCollisions(sf::IntRect bounds);
    void checkCollisions(GameObject &obj, uint range);


    bool running;
    bool canRun;
};

#endif