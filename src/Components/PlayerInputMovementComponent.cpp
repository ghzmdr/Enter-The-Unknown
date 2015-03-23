#include "Components/PlayerInputMovementComponent.hpp"

#include "Entities/Entity.hpp"

void PlayerInputMovementComponent::update(Entity &parent)
{
    parent.running = sf::Keyboard::isKeyPressed(sf::Keyboard::Z);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        move(Direction::Left, parent);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        move(Direction::Right, parent);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        move(Direction::Up, parent);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        move(Direction::Down, parent);

    MovementComponent::update(parent);
}