#include "Player.hpp"
#include "Debug.h"
Player::Player()
{
    setSpeed(playerSpeed);
    setLives(playerLives);
}

void Player::update()
{
   Entity::update();
}

