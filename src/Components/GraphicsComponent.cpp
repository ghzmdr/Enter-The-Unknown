#include "Components/GraphicsComponent.hpp"

#include "Entities/Entity.hpp"

GraphicsComponent::GraphicsComponent(sf::Texture &texture, sf::IntRect textureRect)
: texture{texture}, textureRect{textureRect}
{
    drawable.setPrimitiveType(sf::Quads);
    drawable.resize(4);

    float left =    textureRect.left;
    float right =   left + textureRect.width;
    float top =     textureRect.top;
    float bottom =  top + textureRect.height;
    
    drawable[0].texCoords = {left,top};    
    drawable[1].texCoords = {left, bottom};    
    drawable[2].texCoords = {right, bottom};    
    drawable[3].texCoords = {right, top};
}

void GraphicsComponent::update(GameObject &parent)
{

    float   left = parent.left(),
            top = parent.top(),
            bottom = parent.bottom(),
            right = parent.right();

    drawable[0].position = {left, top};
    drawable[1].position = {left, bottom};
    drawable[2].position = {right, bottom};
    drawable[3].position = {right, top};
}
