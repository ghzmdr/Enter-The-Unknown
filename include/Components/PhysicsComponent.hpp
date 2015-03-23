#ifndef PHISYCS_COMPONENT
#define PHISYCS_COMPONENT

#include "Entities/GameObject.hpp"
#include <SFML/Graphics/Rect.hpp>
#include "Entities/Obstacle.hpp"
#include "Component.hpp"
#include <vector>

class Entity;
class Floor;

class PhysicsComponent : Component
{
public:

    PhysicsComponent(){};

    virtual void update(Entity &parent, Floor &floor);

    void checkCollisions(std::vector<Obstacle> &colliders, Entity &parent);
    bool isObjectInRange(GameObject &obj, GameObject &test);
    void checkBounds(sf::IntRect &bounds, Entity &parent);
   
    bool intersects(GameObject &obj);

private:
    const short range = 16;
};

#endif