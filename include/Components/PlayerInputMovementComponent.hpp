#ifndef PLAYER_INPUT_COMPONENT_HPP
#define PLAYER_INPUT_COMPONENT_HPP

#include "Components/MovementComponent.hpp"
#include <SFML/Window/Keyboard.hpp>
#include "Loaders/InputLoader.hpp"

class PlayerInputMovementComponent : public MovementComponent
{
public:
    PlayerInputMovementComponent();
    virtual void update(Entity &parent);    

private:
    sf::Keyboard::Key left, right, up, down;
};


#endif
