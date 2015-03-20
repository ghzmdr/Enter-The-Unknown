#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "GameObject.hpp"


class Entity : public GameObject
{

public:
static constexpr float defaultSpeed {1.5}, diagonalFactor {1.2}, runFactor {1.5};
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

    void setRunning(bool flag);
    bool isRunning();

    void walk(Direction dir);

    void checkCollisions(GameObject &obj, uint range);
    void checkCollisions(sf::IntRect bounds);
    bool collides(GameObject &obj);

    void setWalkingAnimFrames(std::vector<u_short> frames);
    void setAttackingAnimFrames(std::vector<u_short> frames);
    void setDyingAnimFrames(std::vector<u_short> frames);

protected:
    virtual void animate();
    void reset();
    bool isObjectInRange(GameObject &obj, uint range);
    bool canGoLeft = true, canGoRight = true, canGoUp = true, canGoDown = true;

    uint lives;
    float speed;

    bool walking;
    bool running;
    bool canRun;
    
    u_short framesSkipped;    
    sf::Vector2f velocity;

    u_short currentFrame;

    std::vector<u_short> walkingFrames;
    std::vector<u_short> attackingFrames;
    std::vector<u_short> dyingFrames;   
};

#endif