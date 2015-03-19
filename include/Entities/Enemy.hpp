#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "Entity.hpp"

class Enemy : public Entity
{
public:
    Enemy();

    virtual void animate();

    void setDamage(u_short amount);
    u_short getDamage();


private:    
    u_short damage;


    //Every enemy has:
    // + Scripted rules
    // + An amount of damage dealt
    // + A range in which he can see the player (and so a pointer to it)
    // + A spawn position
    // + A weapon (??)
    // + An animation associated with a spritesheet (Should be standardized)
    //      + First row is walking animation
    //      + Second row is attacking animation
    //      + Third row is death animation

};

#endif