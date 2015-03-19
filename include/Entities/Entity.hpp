#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "GameObject.hpp"


class Entity : public GameObject
{

public:
static constexpr float defaultSpeed {1.5}, diagonalFactor {1.2};
static constexpr u_short animSkipFrames{10};
enum class Direction { Left, Right, Up, Down };

public:

    Entity();
    virtual void update();

    void takeDamage(int amount=1);
    uint getLives() const;
    void setLives(uint amount);

    bool isAlive() const;

    float getSpeed();
    void setSpeed(float amount);

    void walk(Direction dir);

    void checkCollisions(GameObject &obj, uint range);
    void checkCollisions(sf::IntRect bounds);

protected:
    virtual void animate() = 0;
    bool isObjectInRange(GameObject &obj, uint range);
    bool canGoLeft = true, canGoRight = true, canGoUp = true, canGoDown = true;

    uint lives;
    float speed;

    bool walking;
    u_short framesSkipped;    
    sf::Vector2f velocity;
};

#endif