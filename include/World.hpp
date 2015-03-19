#ifndef LEVEL_H
#define LEVEL_H

#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics.hpp>

#include "SceneNode/SceneNode.hpp"
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
    void drawStats();

    bool isInBounds(sf::Sprite &tile);

    int drawOffset;

    sf::View worldView;

    sf::IntRect bounds;

    std::vector<sf::Sprite> bgLayer;
    std::vector<GameObject> collidablesLayer;

    template<typename Object>
    void map2Layer(const std::vector<std::vector<int>> &source, std::vector<Object> &destination, int tileSize, int rowMax);
    void movePlayer();

	State::Context context;
    u_short tileSize;

    TextureManager &textures;
    FontManager &fonts;

    WorldData data;

    sf::Text stats;
    Player player;
};

#endif