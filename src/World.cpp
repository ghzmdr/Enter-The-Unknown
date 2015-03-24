#include "World.hpp"

#include "Debug.h"
#include "Utils/Utility.hpp"


World::World(State::Context con, const std::string &floorFileName)
: context{*(con.window), *(con.textures), *(con.fonts)},
textures(*(con.textures)), fonts(*(con.fonts)), drawStatsFlag{false}
{
    stats.setFont(fonts[Fonts::Main]);
    stats.setCharacterSize(15);
    
    currentFloor = FloorFactory("data/floors/testfloor/testfloor.json", textures);
    player = EntityFactory("data/players/dimitri/dimitri.json", textures, false);
    log_info("SPAWN: %d %d", currentFloor->spawnPosition.x, currentFloor->spawnPosition.x);
    player->position.x = currentFloor->spawnPosition.x;
    player->position.y = currentFloor->spawnPosition.y;
    
    worldView.zoom(.5);
    worldView.setSize(context.window->getSize().x/2, context.window->getSize().y/2);
    worldView.setCenter(player->position);
}

void World::update(sf::Time deltaT)
{
    currentFloor->update(deltaT);
    currentFloor->viewBounds = {worldView.getCenter().x, worldView.getCenter().y, worldView.getSize().x,  worldView.getSize().y};

    stats.setString("Player Speed: " + toString(player->lastSpeed) + "\ntop: " + toString(player->top()) + "\nright: " + toString(player->right()) + "\nbottom: " + toString(player->bottom()) + "\nleft: " + toString(player->left()));
    player->update(*currentFloor);
}

void World::draw()
{
    worldView.setCenter(player->position);
    context.window->setView(worldView);

    context.window->draw(*currentFloor);
    context.window->draw(*player);

   if (drawStatsFlag) drawStats();
}

void World::drawStats()
{
    stats.setPosition(50, 50);
    context.window->setView(context.window->getDefaultView());
    context.window->draw(stats);
}

void World::handleEvent(const sf::Event &event)
{
    if (event.type == sf::Event::KeyPressed)
        switch(event.key.code)
        {
            case sf::Keyboard::F1:
                currentFloor->drawBoundings = !currentFloor->drawBoundings;
            case sf::Keyboard::F2:
                drawStatsFlag = !drawStatsFlag;
        }

    if (event.type == sf::Event::MouseWheelMoved)
    {
        printf("Zoom: %d\n", event.mouseWheel.delta);
        //worldView.zoom(worldView.ge)
    }
}