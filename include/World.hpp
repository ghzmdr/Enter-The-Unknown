#ifndef LEVEL_H
#define LEVEL_H

#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics.hpp>

#include "States/State.hpp"
#include "Player.hpp"

#include "TileMap.hpp"

#include "Utils/EntityLoader.hpp"
#include "Utils/FloorLoader.hpp"

#include "Resource/Resources.hpp"

class World : private sf::NonCopyable
{
public:
	explicit World(State::Context context, const std::string &floorFileName);

	void update(sf::Time deltaT);
	void draw();
    void handleEvent(const sf::Event& event);

private:    
    void loadData();

    template<typename Object>
    void map2Layer(const std::vector<std::vector<short>> &source, std::vector<Object> &destination, int tileSize, int rowMax);
    std::vector<sf::Sprite> bgLayer;
    std::vector<GameObject> collidablesLayer;

    sf::IntRect bounds;
    bool isInBounds(sf::Sprite &tile);

    sf::View worldView;
    
    int drawOffset;    
    void movePlayer();

    u_short tileSize;
    
    sf::Text stats;
    void drawStats();

    FloorLoader floorData;

    TileMap tileMap;

    State::Context context;
    TextureManager &textures;
    FontManager &fonts;
    Player player;
};

#endif