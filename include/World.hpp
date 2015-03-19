#ifndef LEVEL_H
#define LEVEL_H

#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics.hpp>

#include "States/State.hpp"
#include "WorldData.hpp"
#include "Player.hpp"

#include "Resource/Resources.hpp"

class World : private sf::NonCopyable
{
public:
	explicit World(State::Context context, WorldData data);

	void update(sf::Time deltaT);
	void draw();
    void handleEvent(const sf::Event& event);

private:    
    void loadData();
    WorldData data;

    template<typename Object>
    void map2Layer(const std::vector<std::vector<int>> &source, std::vector<Object> &destination, int tileSize, int rowMax);
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

    State::Context context;
    TextureManager &textures;
    FontManager &fonts;
    Player player;
};

#endif