#ifndef MOVEMENT_COMPONENT
#define MOVEMENT_COMPONENT

#include "Component.hpp"

class Entity;

class MovementComponent : Component
{
public: 
    enum class Direction { Left, Right, Up, Down };

public:
    MovementComponent(){};

    virtual void update(Entity &parent);

protected:
    void move(Direction dir, Entity &parent);
};


#endif