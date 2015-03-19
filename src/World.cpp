#include "World.hpp"

#include "Debug.h"
#include "Utils/Utility.hpp"
#include <sstream>


World::World(State::Context con, const std::string &floorFileName)
:context{con}, textures{*(con.textures)}, fonts{*(con.fonts)},
floorData{floorFileName}
{        
    stats.setFont(fonts[Fonts::Main]);
    stats.setCharacterSize(15);
    textures[Textures::WorldTiles].setSmooth(false);


    EntityLoader playerLoader{"./data/player/player.json"};

    player.setTexture(textures[playerLoader.getSheetFileName()]);
    auto psize = playerLoader.getSize();
    player.setTextureRect({0,0,psize.x,psize.y});

    player.setPosition(floorData.getSpawnPosition().x, floorData.getSpawnPosition().y);
    
    player.setWalkingAnimFrames(playerLoader.getMovementFrames());

    worldView.zoom(.5);
    worldView.setSize(context.window->getSize().x/2, context.window->getSize().y/2);
    worldView.setCenter(player.getPosition());

    loadData();
}

void World::loadData()
{   
    tileSize = floorData.getTileSize();
    drawOffset = tileSize * 2;    
    
    auto fSize = floorData.getFloorSize();
    bounds = {{0,0,}, fSize};
    
    auto map = floorData.getMap();
    tileMap.load(textures[Textures::WorldTiles], map, floorData.getTileSize());

    sf::Vector2u tileSheetSize = textures[Textures::WorldTiles].getSize();

    int maxTilesInRow = tileSheetSize.x / tileSize;

    //map2Layer(floorData.getMap(), bgLayer, tileSize, maxTilesInRow);
    map2Layer(floorData.getCollidables(), collidablesLayer, tileSize, maxTilesInRow);
    
}

void World::update(sf::Time deltaT)
{                
    player.setRunning(sf::Keyboard::isKeyPressed(sf::Keyboard::Z));
    movePlayer();
    stats.setString("Player Speed: " + toString(player.getSpeed()) + "\ntop: " + toString(player.top()) + "\nright: " + toString(player.right()) + "\nbottom: " + toString(player.bottom()) + "\nleft: " + toString(player.left()));    
    player.update();    
}

void World::draw()
{       
    worldView.setCenter(player.getPosition());    
    context.window->setView(worldView);       
/*

    for (auto &tile : bgLayer) 
       if (isInBounds(tile))
            context.window->draw(tile);            
*/  
    context.window->draw(tileMap);
    context.window->draw(player);

    for (auto &obj : collidablesLayer)
        if (isInBounds(obj))
            context.window->draw(obj);

   drawStats();
}

void World::drawStats()
{
    stats.setPosition(50, 50);
    context.window->setView(context.window->getDefaultView());
    context.window->draw(stats);
}

void World::handleEvent(const sf::Event& event)
{           
}

void World::movePlayer()
{   
    float playerSpeed = player.getSpeed();
        
    for(auto &obj : collidablesLayer)     
        player.checkCollisions(obj, tileSize);
        
    player.checkCollisions(bounds);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        player.walk(Player::Direction::Left);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        player.walk(Player::Direction::Right);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        player.walk(Player::Direction::Up);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))        
        player.walk(Player::Direction::Down);    
}



bool World::isInBounds(sf::Sprite &tile)
{
    //TILE LEFT X IS > WORLD LEFT X (WORLD CENTER X - HALF WORLD WIDTH)
    bool inLeft = tile.getPosition().x >= worldView.getCenter().x - (worldView.getSize().x/2 + drawOffset);

    //TILE LEFT X IS < WORLD RIGHT X (WORLD CENTER X + HALF WORLD WIDTH)
    bool inRight = tile.getPosition().x <= worldView.getCenter().x + (worldView.getSize().x/2 + drawOffset);

    //TILE TOP Y > WORLD TOP Y (WORLD CENTER Y - HALF WORLD HEIGHT)
    bool inTop = tile.getPosition().y >= worldView.getCenter().y - (worldView.getSize().y/2 + drawOffset);

    //TILE BOTTOM Y < WORLD BOTTOM Y (WORLD CENTER Y + HALF WORLD HEIGHT)
    bool inBottom = tile.getPosition().y <= worldView.getCenter().y + (worldView.getSize().y/2 + drawOffset);

    if (inLeft && inRight && inTop && inBottom) 
        return true;

    return false;
}

template<typename Object>
void World::map2Layer(const std::vector<std::vector<short>> &source, std::vector<Object> &destination, int tileSize, int rowMax)
{
    for (int i = 0; i < source.size(); i++)
        for (int j = 0; j < source[i].size(); j++)
            if (source[i][j] >= 0)
            {
                sf::Vector2i tilePosition = {source[i][j] * tileSize, (source[i][j] * tileSize) % rowMax};
                Object tile{textures[Textures::WorldTiles], {tilePosition, {tileSize, tileSize}}};
                tile.setPosition(j * tileSize , i * tileSize);                
                destination.push_back(tile);
            }
}
