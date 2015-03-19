#include "Entities/RunningEntity.hpp"

RunningEntity::RunningEntity()
: canRun{true}, running{false}
{}

void RunningEntity::checkCollisions(GameObject &obj, uint range)
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

void RunningEntity::checkCollisions(sf::IntRect bounds)
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


float RunningEntity::getSpeed()
{
    if (running) return Entity::getSpeed() * runFactor;
    else return Entity::getSpeed();
}

void RunningEntity::update()
{
    if (running && canRun) 
    {
        velocity.x *= runFactor;
        velocity.y *= runFactor;
    }

    canRun = true;
    running = false;    
    Entity::update();
}