#include "World.hpp"

#include "Debug.h"
#include "Utils/Utility.hpp"


World::World(State::Context con, const std::string &floorFileName)
: context{*(con.window), *(con.textures), *(con.fonts)},
textures(*(con.textures)), fonts(*(con.fonts)), drawStatsFlag{false}
{
    stats.setFont(fonts[Fonts::Main]);
    stats.setCharacterSize(15);

    loadFloor();
    loadPlayer();

    worldView.zoom(.5);
    worldView.setSize(context.window->getSize().x/2, context.window->getSize().y/2);
    worldView.setCenter(player->position);
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

    auto psize = playerLoader.getSize();

    GraphicsComponent *gr = new GraphicsComponent(textures[playerLoader.getSheetFileName()], {0,0,psize.x,psize.y});
    player = std::unique_ptr<Entity>(new Entity(&input, &physics, gr));

    auto pSpawn = currentFloor.spawnPosition;
    player->position = {pSpawn.x * 1.f, pSpawn.y * 1.f};
    player->speed = 2;
    player->size = {psize.x * 1.f, psize.y * 1.f};

    //player.setWalkingAnimFrames(playerLoader.getMovementFrames());
}

void World::update(sf::Time deltaT)
{
    currentFloor.update(deltaT);
    currentFloor.viewBounds = {worldView.getCenter().x, worldView.getCenter().y, worldView.getSize().x,  worldView.getSize().y};

    stats.setString("Player Speed: " + toString(player->lastSpeed) + "\ntop: " + toString(player->top()) + "\nright: " + toString(player->right()) + "\nbottom: " + toString(player->bottom()) + "\nleft: " + toString(player->left()));
    player->update(currentFloor);
/*
    if (player.collides(currentFloor.getExit()))
        printf("WININININININ\n");
*/
}

void World::draw()
{
    worldView.setCenter(player->position);
    context.window->setView(worldView);

    context.window->draw(currentFloor);
    context.window->draw(*player);

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

std::unique_ptr<Entity> World::playerFactory()
{
 //   new GraphicsComponent(, sf::FloatRect textureRect)
 //   return std::unique_ptr<Entity>(new Entity(&input, &physics));
}
