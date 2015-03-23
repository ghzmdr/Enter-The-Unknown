#include "Entities/Obstacle.hpp"


Obstacle::Obstacle(GraphicsComponent *gr, sf::Vector2f position, sf::Vector2i size)
: graphics{gr}
{
    GameObject::position = {position.x, position.y};
    GameObject::size = {size.x * 1.f, size.y * 1.f};
    graphics->update(*this);}


void Obstacle::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.texture = &(graphics->texture);        
    target.draw(graphics->drawable, states);
}
 