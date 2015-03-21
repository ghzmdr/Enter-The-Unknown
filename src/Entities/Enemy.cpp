#include "Entities/Enemy.hpp"
#include "Utils/EntityLoader.hpp"

Enemy::Enemy()
{
}

void Enemy::setDamage(unsigned short amount){damage = amount;}
unsigned short Enemy::getDamage(){return damage;}

void Enemy::animate()
{
}
