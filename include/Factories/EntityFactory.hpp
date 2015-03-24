#ifndef ENTITY_FACTORY
#define ENTITY_FACTORY

#include <string>
#include <memory>

#include "Entities/Entity.hpp"
#include "Loaders/EntityLoader.hpp"

#include "Components/PlayerInputMovementComponent.hpp"

#include "Resource/Resources.hpp"

//Implement hot reaload

std::unique_ptr<Entity> static EntityFactory(const std::string &filename, TextureManager &textures, bool aiControlled)
{ 

    EntityLoader entityData{filename};

    auto sz = entityData.getSize();
    std::unique_ptr<GraphicsComponent> gr(new GraphicsComponent(textures[entityData.getSheetFileName()], {0,0,sz.x,sz.y}));
   
    std::unique_ptr<MovementComponent> mv;

    if (!aiControlled)
        mv  = std::unique_ptr<MovementComponent>(new PlayerInputMovementComponent());
    // else load ai script and ai component

    std::unique_ptr<PhysicsComponent> ph(new PhysicsComponent());
    std::unique_ptr<AnimationComponent> an(new AnimationComponent());

    std::unique_ptr<Entity> eptr(new Entity(std::move(mv),std::move(ph),std::move(gr),std::move(an)));

    eptr->speed = entityData.getSpeed();
    eptr->runFactor = entityData.getRun();
    
    eptr->size = {(float)sz.x,(float) sz.y};

    return std::move(eptr);
}

#endif