#ifndef TILEMAP_HPP
#define TILEMAP_HPP

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/VertexArray.hpp>

class TileMap : public sf::Drawable, public sf::Transformable
{
public:
    TileMap(){};

    void load(sf::Texture &texture, std::vector<std::vector<short>> &tiles, u_short tileSize)
    {
        tilesheet = texture;
        vertices.setPrimitiveType(sf::Quads);
        vertices.resize(tiles.size() * tiles[0].size() * 4);

         for (int i = 0; i < tiles.size(); i++)
            for (int j = 0; j < tiles[0].size(); j++)
            {
                auto tileID = tiles[i][j];
                if (tileID >=0)
                {
                    int tileX = tileID % (tilesheet.getSize().x / tileSize);
                    int tileY = tileID / (tilesheet.getSize().x / tileSize);

                    sf::Vertex *quad = &vertices[(i + j * tiles.size()) * 4];

                    quad[0].position = sf::Vector2f(j * tileSize, i * tileSize -0.0075);
                    quad[1].position = sf::Vector2f((j+1) * tileSize, i * tileSize -0.0075);
                    quad[2].position = sf::Vector2f((j+1) * tileSize, (i+1) * tileSize -0.0075);
                    quad[3].position = sf::Vector2f(j * tileSize, (i + 1) * tileSize -0.0075);

                    quad[0].texCoords = sf::Vector2f(tileX * tileSize, tileY * tileSize);
                    quad[1].texCoords = sf::Vector2f((tileX+1) * tileSize, tileY * tileSize);
                    quad[2].texCoords = sf::Vector2f((tileX+1) * tileSize, (tileY+1) * tileSize);
                    quad[3].texCoords = sf::Vector2f(tileX * tileSize, (tileY + 1) * tileSize);
                } 
            }
    }

private:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const
    {
        states.transform *= getTransform();
        states.texture = &tilesheet;
        target.draw(vertices, states);
    }

    sf::Texture tilesheet;
    sf::VertexArray vertices;
};

#endif