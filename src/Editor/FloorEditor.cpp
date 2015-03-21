#include "Editor/FloorEditor.hpp"

#include "Debug.h"
#include "Utils/Utility.hpp"

FloorEditor::FloorEditor(State::Context con)
: context(*(con.window), *(con.textures), *(con.fonts)),
textures(*context.textures), fonts(*context.fonts)
{
    loadFloor();
    loadPlayer();

    tilesView.setViewport(sf::FloatRect(0,0,.2f,1));
    view.setViewport(sf::FloatRect(.2f,0,.8f, 1));
    view.zoom(.5);
    view.setSize(context.window->getSize().x/2, context.window->getSize().x/2);
    view.setCenter(player.getPosition());
}

void FloorEditor::loadFloor()
{
    currentFloor.tileSize = 16;
    currentFloor.setTileSheet(textures["res/img/floors/ground.png"]);
    currentFloor.loadTileMap({{0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}});
    currentFloor.spawnPosition = {0 + currentFloor.tileSize/2, 0 + currentFloor.tileSize/2};
    currentFloor.drawBoundings = true;
}

void FloorEditor::loadPlayer()
{
    EntityLoader playerLoader{"data/players/dimitri/dimitri.json"};
    player.setTexture(textures[playerLoader.getSheetFileName()]);
    auto psize = playerLoader.getSize();
    player.setTextureRect({0,0,psize.x,psize.y});
    auto pSpawn = currentFloor.spawnPosition;
    player.setPosition(pSpawn.x, pSpawn.y);
    player.setWalkingAnimFrames(playerLoader.getMovementFrames());
}

void FloorEditor::update(sf::Time deltaT)
{
    currentFloor.viewBounds = {view.getCenter().x, view.getCenter().y, view.getSize().x,  view.getSize().y};
    currentFloor.update(deltaT);

    sf::Vector2i movement{0,0};

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        movement.x -= 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        movement.x += 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        movement.y -= 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        movement.y += 1;
}

void FloorEditor::draw()
{
    context.window->setView(tilesView);

    sf::RectangleShape leftPanelBG;
    leftPanelBG.setSize(tilesView.getSize());
    leftPanelBG.setFillColor({130,130,130});
    leftPanelBG.setPosition(0,0);
    context.window->draw(leftPanelBG);

    context.window->setView(view);

    context.window->draw(currentFloor);
    //context.window->draw(player);
}

void FloorEditor::handleEvent(const sf::Event& event)
{
    if (event.type == sf::Event::MouseButtonPressed)
        if(event.mouseButton.button == sf::Mouse::Left)
            addTileAt(sf::Mouse::getPosition(*(sf::Window*)context.window));
}

void FloorEditor::addTileAt(sf::Vector2i position)
{
    auto pos = position;
    pos.x /= currentFloor.tileSize;
}
