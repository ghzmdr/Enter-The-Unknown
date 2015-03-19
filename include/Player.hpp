#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Entities/RunningEntity.hpp"

class Player : public RunningEntity
{
    
static constexpr float playerSpeed{1.5};
static constexpr uint playerLives{5};

public:
    Player();    
    virtual void update();
private:
   virtual void animate();
};

#endif