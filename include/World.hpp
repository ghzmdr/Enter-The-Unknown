#ifndef LEVEL_H
#define LEVEL_H

#include <SFML/Graphics.hpp>

#include "States/State.hpp"

#include "Entities/Entity.hpp"
#include "Floor.hpp"

#include "Factories/FloorFactory.hpp"
#include "Factories/EntityFactory.hpp"

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
    bool drawStatsFlag;
    
    std::unique_ptr<Entity> player;
    std::unique_ptr<Floor> currentFloor;
    
    sf::View worldView;    
    
    sf::Text stats;
    void drawStats();

    State::Context context;
    TextureManager &textures;
    FontManager &fonts;
};

#endif