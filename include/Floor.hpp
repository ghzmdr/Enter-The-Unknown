#ifndef FLOOR_HPP
#define FLOOR_HPP

#include <SFML/Graphics.hpp>

#include "TileMap.hpp"
#include "Entities/GameObject.hpp"
#include "Entities/Obstacle.hpp"
#include "Factories/EntityFactory.hpp"

#include <memory>

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

    std::vector<Obstacle> getCollidables(){return collidables;}

    void loadEnemies(std::vector<EnemyData> enemiesData);

    sf::IntRect bounds;
    sf::FloatRect viewBounds;
    unsigned short tileSize;

    sf::Vector2i spawnPosition;
    void setExit(sf::Vector2i pos)
    {
        exit.position = {pos.x * 1.f, pos.y * 1.f};
        //exit.setTexture(tileSheet);
        //exit.setTextureRect({{(int)tileSheet.getSize().x / tileSize, (int)tileSheet.getSize().y / tileSize}, {tileSize, tileSize}});
    }

    GameObject& getExit() {return exit;}

    bool drawBoundings;
    std::vector<Obstacle> collidables;
private:
    const unsigned short drawOffset = 2;

    const bool isInBounds(const sf::Vector2f &tile) const;
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

    TileMap tileMap;

    sf::Texture tileSheet;
    
    std::vector<sf::RectangleShape> boundings;

    GameObject exit;

    std::vector<std::unique_ptr<Entity>> enemies;

    void map2Layer(const MapData &source);
};

#endif
