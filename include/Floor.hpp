#ifndef FLOOR_HPP
#define FLOOR_HPP

#include <SFML/Graphics.hpp>

#include "TileMap.hpp"
#include "GameObject.hpp"

class Floor : private sf::NonCopyable, public sf::Drawable, public sf::Transformable
{
public:
    typedef std::vector<std::vector<short>> MapData;

public: 
    Floor(): drawBoundings{false}{};

    void update(sf::Time deltaT);
    void handleEvent(const sf::Event &event){};

    void setTileSheet(sf::Texture &ts);
    void loadTileMap(MapData map);
    void loadCollidables(MapData map);

    std::vector<GameObject> getCollidables(){return collidables;}

    sf::IntRect bounds;
    sf::FloatRect viewBounds;
    u_short tileSize;

    sf::Vector2i spawnPosition;
    void setExit(sf::Vector2i pos)
    {
        exit.setPosition(pos.x, pos.y);
        exit.setTexture(tileSheet); 
        exit.setTextureRect({{(int)tileSheet.getSize().x / tileSize, (int)tileSheet.getSize().y / tileSize}, {tileSize, tileSize}});        
    }

    GameObject& getExit() {return exit;}

    bool drawBoundings;
private:
    const u_short drawOffset = 2;

    const bool isInBounds(const sf::Vector2f &tile) const;
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

    TileMap tileMap;

    sf::Texture tileSheet;
    std::vector<GameObject> collidables;

    std::vector<sf::RectangleShape> boundings;

    GameObject exit;

    template<typename Object>
    void map2Layer(const MapData &source, std::vector<Object> &destination);

};

#endif