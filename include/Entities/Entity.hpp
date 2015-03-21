#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "GameObject.hpp"


class Entity : public GameObject
{

public:
static constexpr float defaultSpeed {1.5}, diagonalFactor {1.2}, runFactor {1.5};
static constexpr unsigned short animSkipFrames{10};
enum class Direction { Left, Right, Up, Down };

public:

    Entity();
    virtual void update();

    void takeDamage(int amount=1);
    unsigned short getLives() const;
    void setLives(unsigned short amount);

    bool isAlive() const;

    float getSpeed();
    void setSpeed(float amount);

    void setRunning(bool flag);
    bool isRunning();

    void walk(Direction dir);

    void checkCollisions(GameObject &obj, unsigned short range);
    void checkCollisions(sf::IntRect bounds, unsigned short tileSize);
    bool collides(GameObject &obj);

    void setWalkingAnimFrames(std::vector<unsigned short> frames);
    void setAttackingAnimFrames(std::vector<unsigned short> frames);
    void setDyingAnimFrames(std::vector<unsigned short> frames);

protected:
    virtual void animate();
    void reset();
    bool isObjectInRange(GameObject &obj, unsigned short range);
    bool canGoLeft = true, canGoRight = true, canGoUp = true, canGoDown = true;

    unsigned short lives;
    float speed;

    bool walking;
    bool running;
    bool canRun;

    unsigned short framesSkipped;
    sf::Vector2f velocity;

    unsigned short currentFrame;

    std::vector<unsigned short> walkingFrames;
    std::vector<unsigned short> attackingFrames;
    std::vector<unsigned short> dyingFrames;
};

#endif
