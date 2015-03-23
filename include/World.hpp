#ifndef LEVEL_H
#define LEVEL_H

#include <SFML/Graphics.hpp>

#include "States/State.hpp"

#include "Entities/Entity.hpp"
#include "Floor.hpp"

#include "Utils/EntityLoader.hpp"
#include "Utils/FloorLoader.hpp"

#include "Resource/Resources.hpp"

#include "Components/Component.hpp"
#include "Components/PhysicsComponent.hpp"
#include "Components/PlayerInputMovementComponent.hpp"

class World : private sf::NonCopyable
{
public:
	explicit World(State::Context context, const std::string &floorFileName);

    void update(sf::Time deltaT);
    void draw();
    void handleEvent(const sf::Event& event);

private:
    void loadFloor();
    void loadPlayer();
    bool drawStatsFlag;

    template<typename Object>
    void map2Layer(const std::vector<std::vector<short>> &source, std::vector<Object> &destination, int tileSize, int rowMax);

    std::unique_ptr<Entity> playerFactory();

    void movePlayer();
    sf::Text stats;

    void drawStats();
    State::Context context;
    TextureManager &textures;

    FontManager &fonts;
    std::unique_ptr<Entity> player;
    Floor currentFloor;

    sf::View worldView;

    PhysicsComponent physics;
    PlayerInputMovementComponent input;
};

#endif