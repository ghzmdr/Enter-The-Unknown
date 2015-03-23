#include "Components/PhysicsComponent.hpp"

#include "Floor.hpp"
#include "Entities/Entity.hpp"

void PhysicsComponent::update(Entity &parent, Floor &floor)
{
    checkCollisions(floor.collidables, parent);
    checkBounds(floor.bounds, parent);
}

void PhysicsComponent::checkCollisions(std::vector<Obstacle> &colliders, Entity &parent)
{
    float actualSpeed = fabs(parent.lastSpeed);

    for (auto &collider : colliders)
    {
        if (isObjectInRange(collider, parent))
        {
            if (parent.right() >= collider.left() && parent.left() <= collider.right())
            {
                if (parent.top() < collider.top() && parent.bottom() + actualSpeed >= collider.top() && parent.velocity.y >0)
                {
                    if (actualSpeed > parent.speed && parent.bottom() + parent.speed < collider.top())
                        parent.velocity.y = parent.speed;
                    else parent.velocity.y = 0;
                }
                else if (parent.bottom() > collider.bottom() && parent.top() - actualSpeed < collider.bottom() && parent.velocity.y < 0)
                {
                    if (actualSpeed > parent.speed && parent.top() - parent.speed > collider.bottom())
                        parent.velocity.y = -parent.speed;
                    else parent.velocity.y = 0;
                }
            }

            if (parent.bottom() >= collider.top() && parent.top() <= collider.bottom())
            {
                if (parent.left() < collider.left() && (parent.right() + actualSpeed >= collider.left()) && parent.velocity.x >0)
                {
                    if (actualSpeed > parent.speed && parent.right() + parent.speed < collider.left())
                        parent.velocity.x = parent.speed;
                    else parent.velocity.x = 0;
                }
                else if (parent.right() > collider.right() && (parent.left() - actualSpeed <= collider.right()) && parent.velocity.x <0)
                {
                    if (actualSpeed >parent.speed && parent.left() - parent.speed > collider.right())
                        parent.velocity.x = -parent.speed;
                    else parent.velocity.x = 0;
                }
            }
        }
    }
}

bool PhysicsComponent::isObjectInRange(GameObject &obj, GameObject &test)
{
    if (obj.right() < test.left() - range) return false;
    if (obj.left() > test.right() + range) return false;
    if (obj.bottom() < test.top() - range) return false;
    if (obj.top() > test.bottom() + range) return false;
    return true;
}

void PhysicsComponent::checkBounds(sf::IntRect &bounds, Entity &parent)
{
    sf::Vector2f offset{3,3};
    // not absolute!
    float actualSpeed = fabs(parent.lastSpeed);


    if (actualSpeed < parent.speed){
        offset.x += parent.speed - actualSpeed;
        offset.y += parent.speed - actualSpeed;
    }

    offset.y += parent.size.y/4;


    if (parent.velocity.x <0 && parent.left() - actualSpeed <= bounds.left + offset.x) 
    {
        if (actualSpeed > parent.speed && parent.left() - parent.speed > bounds.left + offset.x)        
                parent.velocity.x = -parent.speed;
        else parent.velocity.x = 0;
    }

    else if (parent.velocity.x >0 && parent.right() + actualSpeed >= bounds.width - offset.x) 
    {
        if (actualSpeed > parent.speed && parent.right() + parent.speed < bounds.width - offset.x)
            parent.velocity.x = parent.speed;
        else parent.velocity.x = 0;
    }

    if (parent.velocity.y <0 && parent.top() - actualSpeed <= bounds.top -offset.y)
    {
        if (actualSpeed > parent.speed && parent.top() - parent.speed > bounds.top - offset.y)
            parent.velocity.y = -parent.speed;
        else parent.velocity.y = 0;
    }
    else if (parent.velocity.y >0 && parent.bottom() + actualSpeed >= bounds.height -offset.y)
    {
        if (actualSpeed > parent.speed && parent.bottom() + parent.speed < bounds.height - offset.y)
            parent.velocity.y = parent.speed;
        else parent.velocity.y = 0;
    }
}