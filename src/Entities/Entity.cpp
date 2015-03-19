#include "Entities/Entity.hpp"

Entity::Entity()
: speed{defaultSpeed}, framesSkipped{0}
{}

void Entity::takeDamage(int amount)
{if (isAlive()) lives -= amount;}

uint Entity::getLives() const
{return lives;}

bool Entity::isAlive() const
{ return lives > 0;}

void Entity::setLives(uint amount)
{lives = amount;}


float Entity::getSpeed()
{
    float currentSpeed = speed;

    if (velocity.x != 0 && velocity.y != 0)
    {
        currentSpeed /= diagonalFactor;
    }
    
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

void Entity::checkCollisions(GameObject &obj, uint range)
{
    auto actualSpeed = getSpeed();

    if (isObjectInRange(obj, range))
    {               
        if (!(right() < obj.left()) && !(left() > obj.right()))
        {
            if (top() < obj.top() && bottom() + actualSpeed > obj.top()) 
            {
                 canGoDown = false;
            }
            else if (bottom() > obj.bottom() && top() - actualSpeed < obj.bottom()) 
            {
                canGoUp = false;
            }
        }

        if (!(bottom() < obj.top()) && !(top() > obj.bottom()))
        {
            if (left() < obj.left() && (right() + actualSpeed > obj.left())) 
            {
               canGoRight = false;
            }
            else if (right() > obj.right() && (left() - actualSpeed < obj.right())) 
            {
                 canGoLeft = false;
            }
        }
    }
}

void Entity::checkCollisions(sf::IntRect bounds)
{
    float actualSpeed = getSpeed();

    if (left() - actualSpeed <= bounds.left) canGoLeft = false;
    if (right() + actualSpeed >= bounds.width) canGoRight = false;
    if (top() - actualSpeed <= bounds.top) canGoUp = false;
    if (bottom() + actualSpeed >= bounds.height) canGoDown = false;                                         
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
    
    //If moving diagonally move at lower speed
    if (velocity.x != 0 && velocity.y != 0)
    {
        velocity.x /= diagonalFactor;
        velocity.y /= diagonalFactor;        
    }

    animate();
    move(velocity); 
    velocity.x=0; velocity.y=0;
    walking = false;
    canGoLeft = true, canGoRight = true, canGoUp = true, canGoDown = true;
}