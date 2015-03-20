#ifndef TILEMAP_HPP
#define TILEMAP_HPP

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include <vector>

class TileMap : public sf::Drawable, public sf::Transformable
{
public:
    TileMap();
    void load(sf::Texture &texture, std::vector<std::vector<short>> &tiles, u_short tileSize);
    std::vector<sf::RectangleShape> grid;
private:

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

    sf::Texture tilesheet;
    sf::VertexArray vertices;
};

#endif