#include "Components/PlayerInputMovementComponent.hpp"

#include "Entities/Entity.hpp"

PlayerInputMovementComponent::PlayerInputMovementComponent()
{
    InputLoader i;
    
    left = i.getKLeft();
    right = i.getKRight();
    up = i.getKUp();
    down = i.getKDown();
    run = i.getKRun();
}

void PlayerInputMovementComponent::update(Entity &parent)
{
    parent.running = sf::Keyboard::isKeyPressed(run);

    if (sf::Keyboard::isKeyPressed(left))
        move(Direction::Left, parent);
    if (sf::Keyboard::isKeyPressed(right))
        move(Direction::Right, parent);
    if (sf::Keyboard::isKeyPressed(up))
        move(Direction::Up, parent);
    if (sf::Keyboard::isKeyPressed(down))
        move(Direction::Down, parent);

    MovementComponent::update(parent);    
}