#ifndef PHISYCS_COMPONENT
#define PHISYCS_COMPONENT

#include "Entities/GameObject.hpp"
#include <SFML/Graphics/Rect.hpp>
#include "Entities/Obstacle.hpp"
#include "Component.hpp"
#include <vector>
#include <memory>

class Entity;
class Floor;

class PhysicsComponent : Component
{
public:

    PhysicsComponent(){};

    virtual void update(Entity &parent, Floor &floor);

    void checkCollisions(std::vector<Obstacle> &colliders, Entity &parent);
    void checkCollisions(std::vector<std::unique_ptr<Entity>> &entities, Entity &parent);
    void checkObject(GameObject &collider, Entity &parent, float actualSpeed);

    bool collides(GameObject &obj, GameObject &test);
    
    bool isObjectInRange(GameObject &obj, GameObject &test);
    void checkBounds(sf::IntRect &bounds, Entity &parent);
   
    bool intersects(GameObject &obj);

private:
    const short range = 16;
};

#endif