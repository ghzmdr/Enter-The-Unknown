#include "Components/MovementComponent.hpp"

#include "Entities/Entity.hpp"

void MovementComponent::update(Entity &parent)
{
    parent.moving = parent.velocity.x || parent.velocity.y;
}

void MovementComponent::move(Direction dir, Entity &parent)
{
    float multiplier = 1;
    if (parent.running && parent.canRun) multiplier = parent.runFactor;

    switch (dir)
    {
        case Direction::Left:
            parent.velocity.x -= parent.speed * multiplier; break;
        case Direction::Right:
            parent.velocity.x += parent.speed * multiplier; break;
        case Direction::Up:
            parent.velocity.y -= parent.speed * multiplier; break;
        case Direction::Down:
            parent.velocity.y += parent.speed * multiplier; break;
    }

    //If moving diagonally move at lower speed
    if (parent.velocity.x != 0 && parent.velocity.y != 0)
    {
        parent.velocity.x /= DIAGONAL_FACTOR;
        parent.velocity.y /= DIAGONAL_FACTOR;
    }
}