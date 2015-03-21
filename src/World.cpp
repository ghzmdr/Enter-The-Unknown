#include "World.hpp"

#include "Debug.h"
#include "Utils/Utility.hpp"


World::World(State::Context con, const std::string &floorFileName)
:context{*(con.window), *(con.textures), *(con.fonts)},
textures(*(con.textures)), fonts(*(con.fonts)), drawStatsFlag{false}
{
    stats.setFont(fonts[Fonts::Main]);
    stats.setCharacterSize(15);

    loadFloor();
    loadPlayer();

    worldView.zoom(.5);
    worldView.setSize(context.window->getSize().x/2, context.window->getSize().y/2);
    worldView.setCenter(player.getPosition());
}

void World::loadFloor()
{
    FloorLoader floorData{"data/floors/testfloor/testfloor.json"};
    currentFloor.tileSize = floorData.getTileSize();
    currentFloor.setTileSheet(textures[floorData.getTileSheetFileName()]);
    currentFloor.loadTileMap(floorData.getMap());
    currentFloor.loadCollidables(floorData.getCollidables());
    currentFloor.spawnPosition = floorData.getSpawnPosition();
    currentFloor.setExit(floorData.getExitPosition());
}

void World::loadPlayer()
{
    EntityLoader playerLoader{"data/players/dimitri/dimitri.json"};

    player.setTexture(textures[playerLoader.getSheetFileName()]);

    auto psize = playerLoader.getSize();
    player.setTextureRect({0,0,psize.x,psize.y});

    auto pSpawn = currentFloor.spawnPosition;
    player.setPosition(pSpawn.x, pSpawn.y);

    player.setWalkingAnimFrames(playerLoader.getMovementFrames());
}

void World::update(sf::Time deltaT)
{
    currentFloor.update(deltaT);
    currentFloor.viewBounds = {worldView.getCenter().x, worldView.getCenter().y, worldView.getSize().x,  worldView.getSize().y};

    player.setRunning(sf::Keyboard::isKeyPressed(sf::Keyboard::Z));
    stats.setString("Player Speed: " + toString(player.getSpeed()) + "\ntop: " + toString(player.top()) + "\nright: " + toString(player.right()) + "\nbottom: " + toString(player.bottom()) + "\nleft: " + toString(player.left()));
    movePlayer();
    player.update();

    if (player.collides(currentFloor.getExit()))
        printf("WININININININ\n");

}

void World::draw()
{
    worldView.setCenter(player.getPosition());
    context.window->setView(worldView);

    context.window->draw(currentFloor);
    context.window->draw(player);

   if (drawStatsFlag) drawStats();
}

void World::drawStats()
{
    stats.setPosition(50, 50);
    context.window->setView(context.window->getDefaultView());
    context.window->draw(stats);
}

void World::movePlayer()
{
    float playerSpeed = player.getSpeed();

    for(auto &obj : currentFloor.getCollidables())
        player.checkCollisions(obj, currentFloor.tileSize);

    player.checkCollisions(currentFloor.bounds, currentFloor.tileSize);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        player.walk(Player::Direction::Left);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        player.walk(Player::Direction::Right);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        player.walk(Player::Direction::Up);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        player.walk(Player::Direction::Down);
}

void World::handleEvent(const sf::Event &event)
{
    if (event.type == sf::Event::KeyPressed)
        switch(event.key.code)
        {
            case sf::Keyboard::F1:
                currentFloor.drawBoundings = !currentFloor.drawBoundings;
            case sf::Keyboard::F2:
                drawStatsFlag = !drawStatsFlag;
        }
}
