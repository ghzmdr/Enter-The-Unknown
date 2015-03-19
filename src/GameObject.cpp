#include "GameObject.hpp"
#include "Utils/Utility.hpp"

GameObject::GameObject()
:collidable{true}
{}

GameObject::GameObject(sf::Texture &texture)
:collidable{true}
{setTexture(texture); centerOrigin(*this);}

GameObject::GameObject(sf::Texture &texture, sf::IntRect texRect)
:collidable{true}
{setTexture(texture); setTextureRect(texRect);}

void GameObject::setTextureRect(sf::IntRect rect)
{sf::Sprite::setTextureRect(rect); centerOrigin(*this);}

sf::Vector2i GameObject::getSize()   
{return {getTextureRect().width, getTextureRect().height};}

float GameObject::left()      {return getPosition().x - getTextureRect().width/2;}
float GameObject::right()     {return getPosition().x + getTextureRect().width/2;}    
float GameObject::top()       {return getPosition().y - getTextureRect().height/2;}
float GameObject::bottom()    {return getPosition().y + getTextureRect().height/2;}
