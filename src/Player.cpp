#include "Player.hpp"
#include "Debug.h"
Player::Player()
{
    setSpeed(playerSpeed);
    setLives(playerLives);
}

void Player::update()
{
    RunningEntity::update();
}

void Player::animate()
{
    auto newTextureRect = getTextureRect();
    
    if (framesSkipped > animSkipFrames)
    {   
        if (walking)
        {
            if (newTextureRect.left < getTexture()->getSize().x - newTextureRect.width)
                newTextureRect.left += newTextureRect.width;
            else newTextureRect.left = 0;
        } else newTextureRect.left = 0;

        framesSkipped = 0;
    } else ++framesSkipped;
    
    setTextureRect(newTextureRect);
}
