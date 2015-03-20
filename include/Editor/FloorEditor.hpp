#ifndef FLOOR_EDITOR_HPP
#define FLOOR_EDITOR_HPP 

#include <SFML/Graphics.hpp>

#include "States/State.hpp"

#include "Player.hpp"
#include "Floor.hpp"

#include "Utils/EntityLoader.hpp"

class FloorEditor : private sf::NonCopyable
{
public:
    FloorEditor(State::Context context);

    void update(sf::Time deltaT);
    void draw();
    void handleEvent(const sf::Event& event);
private:

    void addTileAt(sf::Vector2i position);

    void loadFloor();
    void loadPlayer();

    State::Context context;
    TextureManager &textures;
    FontManager &fonts;    

    Player player;    
    Floor currentFloor;
    sf::View view;
    sf::View tilesView;
};

#endif