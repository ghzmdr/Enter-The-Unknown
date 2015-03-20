#include "Entities/Entity.hpp"
#include "Debug.h"

Entity::Entity()
: speed{defaultSpeed}, framesSkipped{0}, currentFrame{0},
canRun{true}, running{false}
{}

void Entity::takeDamage(int amount)
{if (isAlive()) lives -= amount;}

uint Entity::getLives() const
{return lives;}

bool Entity::isAlive() const
{ return lives > 0;}

void Entity::setLives(uint amount)
{lives = amount;}

void Entity::checkCollisions(GameObject &obj, uint range)
{
    auto actualSpeed = getSpeed();

    if (isObjectInRange(obj, range))
    {               
        if (!(right() < obj.left()) && !(left() > obj.right()))
        {
            if (top() < obj.top() && bottom() + actualSpeed > obj.top()) 
            {
                if (running && top() < obj.top() && bottom() + speed <= obj.top())    
                    canRun = false;
                else canGoDown = false;
            }
            else if (bottom() > obj.bottom() && top() - actualSpeed < obj.bottom()) 
            {
                if (running && bottom() > obj.bottom() && top() - speed >= obj.bottom()) 
                    canRun = false;
                else canGoUp = false;
            }
        }

        if (!(bottom() < obj.top()) && !(top() > obj.bottom()))
        {
            if (left() < obj.left() && (right() + actualSpeed > obj.left())) 
            {
                if (running && left() < obj.left() && (right() + speed <= obj.left())) 
                    canRun = false;
                else canGoRight = false;
            }
            else if (right() > obj.right() && (left() - actualSpeed < obj.right())) 
            {
                if (running && left() < obj.left() && (right() + speed <= obj.left())) 
                    canRun = false;
                else canGoLeft = false;
            }
        }
    }
}

bool Entity::collides(GameObject &obj)
{
    return top() <= obj.bottom() && bottom() >= obj.top() && left() <= obj.right() && right() >= obj.left();
}

void Entity::checkCollisions(sf::IntRect bounds)
{
    float actualSpeed = getSpeed();

    if (left() - actualSpeed <= bounds.left)        
        {running && left() - speed > bounds.left ? canRun = false : canGoLeft = false;}
    if (right() + actualSpeed >= bounds.width)
      {running && right() + speed < bounds.width ? canRun = false : canGoRight = false;}
    if (top() - actualSpeed <= bounds.top)
        {running && top() - speed > bounds.top ? canRun = false : canGoUp = false;}
    if (bottom() + actualSpeed >= bounds.height)
        {running && bottom() + speed < bounds.height ? canRun = false : canGoDown = false;}                                        
}

float Entity::getSpeed()
{
    float currentSpeed = speed;

    if (velocity.x != 0 && velocity.y != 0)
    {
        currentSpeed /= diagonalFactor;
    }
 
    if (running) currentSpeed *= runFactor;
    return currentSpeed;
}

void Entity::setSpeed(float amount)
{speed = amount;}

void Entity::walk(Direction dir)
{   
    switch (dir)
    {
        case Direction::Left:
            if (canGoLeft) velocity.x -= speed; break;
        case Direction::Right:
            if (canGoRight) velocity.x += speed; break;
        case Direction::Up:
            if (canGoUp) velocity.y -= speed; break;            
        case Direction::Down:
            if (canGoDown) velocity.y += speed; break;
    }
    walking = velocity.x || velocity.y;
}

bool Entity::isObjectInRange(GameObject &obj, uint range)
{   
    if (obj.right() < left() - range) return false;
    if (obj.left() > right() + range) return false;
    if (obj.bottom() < top() - range) return false;
    if (obj.top() > bottom() + range) return false; 
    return true;
}

void Entity::update()
{
    if (running && canRun) 
    {
        velocity.x *= runFactor;
        velocity.y *= runFactor;
    }
    
    //If moving diagonally move at lower speed
    if (velocity.x != 0 && velocity.y != 0)
    {
        velocity.x /= diagonalFactor;
        velocity.y /= diagonalFactor;        
    }
    
    if (framesSkipped++ >animSkipFrames) animate();

    move(velocity); 
    reset();    
}

void Entity::reset()
{
    canRun = true;
    running = false;    
    velocity.x=0; velocity.y=0;
    walking = false;
    canGoLeft = true, canGoRight = true, canGoUp = true, canGoDown = true;
}

void Entity::animate()
{
    auto newTextureRect = getTextureRect();
    
    if (walking && currentFrame != walkingFrames.back())
        currentFrame ++;
    else currentFrame = walkingFrames.front();
    newTextureRect.left = currentFrame * getSize().x;

    framesSkipped = 0;    
    setTextureRect(newTextureRect);
}

void Entity::setRunning(bool flag)
{running = flag;}

bool Entity::isRunning()
{return running;}

void Entity::setWalkingAnimFrames(std::vector<u_short> frames){walkingFrames = frames;}
void Entity::setAttackingAnimFrames(std::vector<u_short> frames){attackingFrames = frames;}
void Entity::setDyingAnimFrames(std::vector<u_short> frames){dyingFrames = frames;}