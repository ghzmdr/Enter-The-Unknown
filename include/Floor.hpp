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
    const unsigned short drawOffset = 2;

public:
    Floor(): drawBoundings{false}{};

    void update(sf::Time deltaT);
    void handleEvent(const sf::Event &event){};

    void setTileSheet(sf::Texture &ts);
    
    void loadTileMap(MapData map);
    void loadCollidables(MapData map);
    void loadEnemies(std::vector<EnemyData> enemiesData);

    std::vector<Obstacle> getCollidables();
    std::vector<std::unique_ptr<Entity>> getEnemies();

    sf::IntRect bounds;
    sf::FloatRect viewBounds;
    unsigned short tileSize;

    sf::Vector2i spawnPosition;
    
    GameObject& getExit();
    void setExit(sf::Vector2i pos);

    bool drawBoundings;
    std::vector<Obstacle> collidables;
    std::vector<std::unique_ptr<Entity>> enemies;
    TextureManager *textures;
private:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    const bool isInBounds(const sf::Vector2f &tile) const;
    
    std::vector<sf::RectangleShape> boundings;
    
    TileMap tileMap;

    GameObject exit;

    sf::Texture tileSheet;

    void map2Layer(const MapData &source);
};

#endif
