#include "Entities/Enemy.hpp"
#include "Utils/EntityLoader.hpp"

Enemy::Enemy()
{
}

void Enemy::setDamage(u_short amount){damage = amount;}
u_short Enemy::getDamage(){return damage;}

void Enemy::animate()
{
}